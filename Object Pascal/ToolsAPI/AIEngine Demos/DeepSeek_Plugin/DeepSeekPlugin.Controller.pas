unit DeepSeekPlugin.Controller;

interface

uses
  System.SysUtils, REST.Client, Rest.Types, Rest.Json, System.JSON, ToolUtils,
  ToolsAPI.AI, DeepSeekPlugin.Consts, DeepSeekPlugin.Models;

type
  TDeepSeekAIRestClient = class(TOTAClass)
  private
    FRestClient: TCustomRESTClient;
    FRestResponse: TRESTResponse;
    FRestRequest: TRESTRequest;
    FResponseObject: TResponseObj;
    FRequestObj: TRequestObj;
    function IsParsable(var AJsonObj: TJSONObject): Boolean;
    function CheckError(out AValue: string): Boolean;
    procedure DoCompletion(const ARequestID: TGUID);
    procedure DoFinishLoad(const AResponseObj: TResponseObj; const ARequestID: TGUID);
    procedure PrepareBody(const AValue: string);
    procedure PrepareHeader;
    procedure NotifyError(const AMessage: string; const ARequestID: TGUID);
    procedure NotifyAnswer(const AMessage: string; const ARequestID: TGUID);
    function CheckApIKey(const ARequestID: TGUID): Boolean;
  protected
    FBaseURL: string;
    FModel: string;
    FApiKey: string;
    FTimeOut: Integer;
    procedure DoCancel;
    function AddNotifier(const ANotifier: IOTAAIServicesNotifier): Integer;
    procedure RemoveNotifier(const AIndex: Integer);
  public
    constructor Create;
    destructor Destroy; override;
    function DoChat(const APrompt: string; const ARequestID: TGUID): string;
  end;

implementation

{ TDeepSeekAIRestClient }

function TDeepSeekAIRestClient.AddNotifier(const ANotifier: IOTAAIServicesNotifier): Integer;
begin
  Result := AddToList(FNotifyList, ANotifier);
end;

procedure TDeepSeekAIRestClient.RemoveNotifier(const AIndex: Integer);
begin
  FNotifyList[AIndex] := nil;
end;

function TDeepSeekAIRestClient.CheckApIKey(const ARequestID: TGUID): Boolean;
begin
  Result := True;
  if FApiKey.Trim.Equals(EmptyStr) then
  begin
    Result := False;
    NotifyError(cDeepSeekAI_Msg_CheckAPI, ARequestID);
  end;
end;

function TDeepSeekAIRestClient.CheckError(out AValue: string): Boolean;
var
  LJsonObj: TJSONObject;
begin
  Result := False;
  if FRestResponse.Status.ClientErrorBadRequest_400 then
  begin
    if IsParsable(LJsonObj) then
    begin
      var LErrors: TErrorObj;
      try
        LErrors := TJson.JsonToObject<TErrorObj>(TJSONObject(LJsonObj));
        if LErrors <> nil then
        begin
          try
            AValue := LErrors.Error.Message;
            Result := True;
          finally
            LErrors.Free;
          end;
        end;
      finally
        LJsonObj.Free;
      end;
    end
    else
    begin
      try
        AValue := FRestResponse.Content;
      except on E: Exception do
        AValue := E.Message;
      end;
    end;
  end;
end;

constructor TDeepSeekAIRestClient.Create;
begin
  inherited Create;
  FRestClient := TCustomRESTClient.Create(nil);
  FRestResponse := TRESTResponse.Create(nil);
  FRestRequest := TRESTRequest.Create(nil);

  FRestRequest.Method := TRESTRequestMethod.rmPost;
  FRestRequest.Client := FRestClient;
  FRestRequest.Response := FRestResponse;
  FTimeOut := CRestDefaultTimeout;
  FRestRequest.TimeOut := FTimeOut;
  FRestClient.ContentType := TRESTContentType.ctAPPLICATION_JSON;
end;

destructor TDeepSeekAIRestClient.Destroy;
begin
  if Assigned(FRestResponse) then
    FreeAndNil(FRestResponse);

  if Assigned(FRestRequest) then
    FreeAndNil(FRestRequest);

  if Assigned(FRestClient) then
    FreeAndNil(FRestClient);
  inherited;
end;

procedure TDeepSeekAIRestClient.DoCancel;
begin
  if FRestRequest <> nil then
    FRestRequest.Cancel;
end;

function TDeepSeekAIRestClient.DoChat(const APrompt: string; const ARequestID: TGUID): string;
begin
  FRestRequest.Body.ClearBody;
  FRestRequest.Params.Clear;

  PrepareBody(APrompt);
  PrepareHeader;

  if not CheckApIKey(ARequestID) then Exit;
  try
    FRestRequest.ExecuteAsync(
      procedure
      begin
        DoCompletion(ARequestID);
      end,
      True,
      True,
      procedure(AObject: TObject)
      begin
        NotifyError(Exception(AObject).Message, ARequestID);
      end);
  except on E: Exception do
    NotifyError(E.Message, ARequestID);
  end;
end;

procedure TDeepSeekAIRestClient.DoCompletion(const ARequestID: TGUID);
var
  LJsonObj: TJSONObject;
  LErrorMsg: string;
begin
  if FRestRequest = nil then
    Exit;
  if FRestResponse = nil then
    Exit;

  if not FRestResponse.Status.SuccessOK_200 then
  begin
    LErrorMsg := FRestResponse.StatusText;

    var Err: string;
    if CheckError(Err) then
      LErrorMsg := Err;

    NotifyError(LErrorMsg, ARequestID);
    Exit;
  end;

  if not IsParsable(LJsonObj) then
    Exit;

  try
    try
      FreeAndNil(FResponseObject);
      FResponseObject := TJson.JsonToObject<TResponseObj>(TJSONObject(LJsonObj));
      DoFinishLoad(FResponseObject, ARequestID);
    finally
      LJsonObj.Free;
    end;
  except on E: Exception do
    NotifyError(E.Message, ARequestID);
  end;
end;

procedure TDeepSeekAIRestClient.NotifyError(const AMessage: string; const ARequestID: TGUID);
var
  I: Integer;
begin
  FNotifyList.Lock;
  for I := 0 to Pred(FNotifyList.Count) do
    (FNotifyList[I] as IOTAAIServicesNotifier).Error(AMessage, ARequestID);
  FNotifyList.Unlock;
end;

procedure TDeepSeekAIRestClient.DoFinishLoad(const AResponseObj: TResponseObj; const ARequestID: TGUID);
var
  LMessage: string;
begin
  if AResponseObj = nil then
    LMessage := cDeepSeekAI_Msg_NoAnswer
  else
    LMessage := AResponseObj.Choices[0].Message.Content;

  NotifyAnswer(LMessage, ARequestID);
end;

function TDeepSeekAIRestClient.IsParsable(var AJsonObj: TJSONObject): Boolean;
begin
  AJsonObj := nil;
  try
    AJsonObj := TJSONObject.ParseJSONValue(TEncoding.UTF8.GetBytes(FRestResponse.Content), 0) as TJSONObject;
  except
    AJsonObj := nil;
  end;
  Result := AJsonObj <> nil;
end;

procedure TDeepSeekAIRestClient.NotifyAnswer(const AMessage: string; const ARequestID: TGUID);
var
  I: Integer;
begin
  FNotifyList.Lock;
  for I := 0 to Pred(FNotifyList.Count) do
    (FNotifyList[I] as IOTAAIServicesNotifier).Answer(AMessage, ARequestID);
  FNotifyList.Unlock;
end;

procedure TDeepSeekAIRestClient.PrepareBody(const AValue: string);
begin
  FRequestObj := TRequestObj.Create;
  try
    FRequestObj.Model := FModel;
    var LMessage := TMessages.Create;
    LMessage.Role := 'user';
    LMessage.Content := AValue;
    FRequestObj.Messages.Add(LMessage);
    FRestRequest.AddBody(FRequestObj.AsJson, TRESTContentType.ctAPPLICATION_JSON);
  finally
    FreeAndNil(FRequestObj);
  end;
end;

procedure TDeepSeekAIRestClient.PrepareHeader;
begin
  FRestClient.BaseURL := FBaseURL;
  FRestRequest.Timeout := FTimeOut;
  FRestRequest.Params.AddHeader('Authorization', 'Bearer' + ' ' + FApiKey).Options := [poDoNotEncode];
  FRestRequest.Params.AddHeader('Accept', TRESTContentType.ctAPPLICATION_JSON).Options := [poDoNotEncode];
  FRestRequest.Params.AddHeader('Content-Type', TRESTContentType.ctAPPLICATION_JSON).Options := [poDoNotEncode];
end;

end.

