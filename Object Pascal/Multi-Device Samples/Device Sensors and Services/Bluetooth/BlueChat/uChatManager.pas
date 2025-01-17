//---------------------------------------------------------------------------

// This software is Copyright (c) 2015 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

unit uChatManager;

interface

uses
  System.Classes, System.Bluetooth, System.SyncObjs, System.Generics.Collections;

type
  TTextEvent = procedure (const Sender: TObject; const AText: string; const aDeviceName: string) of object;

  TReadThread = class(TThread)
  private
    FOnTextReceived: TTextEvent;
    FName: string;
    FServerSocket: TBluetoothServerSocket;
  protected
    procedure Execute; override;
    procedure TerminatedSet; override;
  public
    constructor Create(const Manager: TBluetoothManager; const Name: string; const AGUID: TGUID); overload;
    destructor Destroy; override;

    property OnTextReceived: TTextEvent read FOnTextReceived write FOnTextReceived;
  end;

  TWriteThread = class(TThread)
  private
    FOnTextSent: TTextEvent;
    FName: string;
    FMessagesBuffer: TList<string>;
    FDevice: TBluetoothDevice;
    FGUID: TGUID;
    FDataInBuffer: TEvent;
    function GetMessagesFromBuffer(out AMessages: TArray<string>): Boolean;
  protected
    procedure Execute; override;
    procedure TerminatedSet; override;
  public
    constructor Create(const Device: TBluetoothDevice; const Name: string; const AGUID: TGUID); overload;
    destructor Destroy; override;

    procedure SendText(const AText: string);

    property OnTextSent: TTextEvent read FOnTextSent write FOnTextSent;
  end;

  TChatManager = class
  private
    FManager: TBluetoothManager;
    FReadThread: TReadThread;
    FWriteThread: TWriteThread;
    FOnTextSent: TTextEvent;
    FOnTextReceived: TTextEvent;
    FOnDiscoveryEnd: TDiscoveryEndEvent;
    FSelectedDevice: Integer;
    FCurrentDevice: TBluetoothDevice;
    FServerGUID: TGUID;
    FClientGUID: TGUID;
    FKnownDevices: TBluetoothDeviceList;
    procedure DiscoveryEnd(const Sender: TObject; const ADeviceList: TBluetoothDeviceList);
    procedure SetOnTextReceived(const Value: TTextEvent);
    procedure SetOnTextSent(const Value: TTextEvent);
    procedure SetSelectedDevice(const Value: Integer);
    procedure SetCurrentDevice(const Value: TBluetoothDevice);
    procedure TeminateThreads;
    procedure InitializeThreads;
    procedure RecreateThreads;
  public
    constructor Create;
    destructor Destroy; override;

    procedure SendText(const AText: string);
    procedure PairTo(const ADevice: string);
    procedure DiscoverDevices;
    function HasBluetoothDevice: boolean;
    procedure UpdateKnownDevices;

    property SelectedDevice: Integer read FSelectedDevice write SetSelectedDevice;
    property CurrentDevice: TBluetoothDevice read FCurrentDevice write SetCurrentDevice;
    property OnTextReceived: TTextEvent read FOnTextReceived write SetOnTextReceived;
    property OnTextSent: TTextEvent read FOnTextSent write SetOnTextSent;
    property OnDiscoveryEnd: TDiscoveryEndEvent read FOnDiscoveryEnd write FOnDiscoveryEnd;
    property KnownDevices: TBluetoothDeviceList read FKnownDevices;
  end;

implementation

uses
  System.SysUtils, System.Math, System.Hash, System.Types;

{ TWriteThread }

constructor TWriteThread.Create(const Device: TBluetoothDevice; const Name: string; const AGUID: TGUID);
begin
  FDevice := Device;
  FGUID := AGUID;
  FName := Name;
  FMessagesBuffer := TList<string>.Create;
  FDataInBuffer := TEvent.Create;
  inherited Create(False);
end;

destructor TWriteThread.Destroy;
begin
  inherited;
  FDevice := nil;
  FreeAndNil(FMessagesBuffer);
  FreeAndNil(FDataInBuffer);
end;

procedure TWriteThread.TerminatedSet;
begin
  inherited;
  if FDataInBuffer <> nil then
    FDataInBuffer.SetEvent;
end;

procedure TWriteThread.Execute;
const
  RetryTimeout = 1000;
var
  LBytesToSend: TBytes;
  LClientSocket: TBluetoothSocket;
  LMessages: TArray<string>;
begin
  while (FDataInBuffer.WaitFor(INFINITE) = TWaitResult.wrSignaled) and not Terminated do
    try
      FDevice.GetServices;
      LClientSocket := FDevice.CreateClientSocket(FGUID, False);
      try
        LClientSocket.Connect;
        try
          while GetMessagesFromBuffer(LMessages) do
          begin
            for var LMessage in LMessages do
              try
                if Terminated then
                  Exit;

                LBytesToSend := TEncoding.UTF8.GetBytes(LMessage);
                LClientSocket.SendData(LBytesToSend);
                if Assigned(FOnTextSent) then
                  FOnTextSent(Self, LMessage, FName);
              except
                if Assigned(FOnTextSent) then
                  FOnTextSent(Self, LMessage + ' "failed to send"', FName);
                Break;
              end;
            end;
        finally
          LClientSocket.Close;
        end;
      finally
        FreeAndNil(LClientSocket);
      end;
    except on E: Exception do
      if not Terminated then
        TThread.Sleep(RetryTimeout);
    end;
end;

function TWriteThread.GetMessagesFromBuffer(out AMessages: TArray<string>): Boolean;
begin
  TMonitor.Enter(FMessagesBuffer);
  try
    Result := FMessagesBuffer.Count > 0;
    if Result then
    begin
      AMessages := FMessagesBuffer.ToArray;
      FMessagesBuffer.Clear;
      FDataInBuffer.ResetEvent;
    end;
  finally
    TMonitor.Exit(FMessagesBuffer);
  end;
end;

procedure TWriteThread.SendText(const AText: string);
begin
  TMonitor.Enter(FMessagesBuffer);
  try
    FMessagesBuffer.Add(AText);
    FDataInBuffer.SetEvent;
  finally
    TMonitor.Exit(FMessagesBuffer);
  end;
end;

{ TReadThread }

constructor TReadThread.Create(const Manager: TBluetoothManager; const Name: string; const AGUID: TGUID);
begin
  FName := Name;
  FServerSocket := Manager.CurrentAdapter.CreateServerSocket('ChatReadSocket ' + Manager.CurrentAdapter.AdapterName, AGUID, False);
  inherited Create(False);
end;

destructor TReadThread.Destroy;
begin
  inherited;
  FreeAndNil(FServerSocket);
end;

procedure TReadThread.TerminatedSet;
begin
  inherited;
  if FServerSocket <> nil then
    FServerSocket.Close;
end;

procedure TReadThread.Execute;
const
  RetryTimeout = 1000;
var
  LBuffer: TBytes;
  LReadSocket: TBluetoothSocket;
begin
  while not Terminated do
    try
      LReadSocket := FServerSocket.Accept(INFINITE);
      if LReadSocket = nil then
        Continue;
      try
        while not Terminated and LReadSocket.Connected do
        begin
          LBuffer := LReadSocket.ReceiveData;
          if (LBuffer <> nil) and Assigned(FOnTextReceived) then
            FOnTextReceived(Self, TEncoding.UTF8.GetString(LBuffer), FName);
        end;
      finally
        FreeAndNil(LReadSocket);
      end;
    except on E: Exception do
      if not Terminated then
        TThread.Sleep(RetryTimeout);
    end;
end;

{ TChatManager }

constructor TChatManager.Create;
begin
  FManager := TBluetoothManager.Current;
  FManager.OnDiscoveryEnd := DiscoveryEnd;
  SelectedDevice := -1;
end;

destructor TChatManager.Destroy;
begin
  TeminateThreads;
  inherited;
end;

procedure TChatManager.DiscoverDevices;
begin
  FManager.OnDiscoveryEnd := DiscoveryEnd;
  FManager.StartDiscovery(5000);
end;

procedure TChatManager.DiscoveryEnd(const Sender: TObject; const ADeviceList: TBluetoothDeviceList);
begin
  if Assigned(FOnDiscoveryEnd) then
    FOnDiscoveryEnd(Sender, ADeviceList);
end;

function TChatManager.HasBluetoothDevice: boolean;
begin
  Result := FManager.CurrentAdapter <> nil;
end;

procedure TChatManager.SendText(const AText: string);
begin
  if FWriteThread <> nil then
  begin
    if FWriteThread.Terminated then
      RecreateThreads;
    FWriteThread.SendText(AText)
  end
  else
    raise Exception.Create('You are not connected to a device');
end;

procedure TChatManager.RecreateThreads;
begin
  TeminateThreads;
  InitializeThreads;
end;

procedure TChatManager.InitializeThreads;

  function CreateGUIDFromName(const AName: string): TGUID;
  var
    LHash: TBytes;
  begin
    LHash := THashMD5.GetHashBytes(AName);
    Result := TGUID.Create(LHash);
  end;

begin
  if FCurrentDevice = nil then
    Exit;

  FServerGUID := CreateGUIDFromName(FManager.CurrentAdapter.AdapterName);
  FClientGUID := CreateGUIDFromName(FCurrentDevice.DeviceName);

  FReadThread := TReadThread.Create(FManager, FCurrentDevice.DeviceName, FServerGUID);
  FReadThread.OnTextReceived := FOnTextReceived;

  FWriteThread := TWriteThread.Create(FCurrentDevice, ' me ', FClientGUID);
  FWriteThread.OnTextSent := FOnTextSent;
end;

procedure TChatManager.PairTo(const ADevice: string);
var
  I: Integer;
  LDevice: TBluetoothDevice;
begin
  LDevice := nil;
  for I := 0 to FManager.LastDiscoveredDevices.Count - 1 do
    if FManager.LastDiscoveredDevices[I].DeviceName = ADevice then
    begin
      LDevice := FManager.LastDiscoveredDevices[I];
      Break;
    end;
  if LDevice <> nil then
    if not LDevice.IsPaired then
      FManager.CurrentAdapter.Pair(LDevice)
end;

procedure TChatManager.TeminateThreads;
begin
  FreeAndNil(FReadThread);
  FreeAndNil(FWriteThread);
end;

procedure TChatManager.UpdateKnownDevices;
begin
  if FManager.CurrentAdapter = nil then
    FKnownDevices := nil
  else
    FKnownDevices := FManager.CurrentAdapter.PairedDevices;
end;

procedure TChatManager.SetCurrentDevice(const Value: TBluetoothDevice);
begin
  FCurrentDevice := Value;
  RecreateThreads;
end;

procedure TChatManager.SetOnTextReceived(const Value: TTextEvent);
begin
  FOnTextReceived := Value;
  if FReadThread <> nil then
    FReadThread.OnTextReceived := Value;
end;

procedure TChatManager.SetOnTextSent(const Value: TTextEvent);
begin
  FOnTextSent := Value;
  if FWriteThread <> nil then
    FWriteThread.OnTextSent := Value;
end;

procedure TChatManager.SetSelectedDevice(const Value: Integer);
begin
  FSelectedDevice := Value;
  if (FKnownDevices <> nil) and InRange(Value, 0, FKnownDevices.Count - 1) then
    CurrentDevice := FKnownDevices[Value]
  else
    CurrentDevice := nil;
end;

end.
