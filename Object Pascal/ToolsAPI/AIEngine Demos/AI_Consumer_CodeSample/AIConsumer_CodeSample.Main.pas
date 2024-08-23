unit AIConsumer_CodeSample.Main;

interface

uses
  ToolsAPI, ToolsAPI.AI, System.Generics.Collections, System.Classes;

type
  TMyAIConsumerNotifier = class(TNotifierObject, IOTAAIServicesNotifier)
  private
    procedure Answer(const AMessage: string; const ARequestID: TGUID);
    procedure Error(const AMessage: string; const ARequestID: TGUID);
    procedure ModelsLoaded(const AModels: TArray<string>; const ARequestID: TGUID);
    procedure ImageLoaded(const AImage: TStream; const ARequestID: TGUID); overload;
    procedure ImageLoaded(const A64BitImages: TArray<string>; const ARequestID: TGUID); overload;
    procedure ImageURlLoaded(const AImageURls: TArray<string>; const ARequestID: TGUID);
    procedure SpeechLoaded(const ASpeech: TStream; const ARequestID: TGUID);
  end;


  {Also it's possible to define specific notifiers based on your needs }
  {    TMyAIConsumerImageNotifier                                      }
  {    TMyAIConsumerSpeechNotifie                                      }
  {    etc                                                             }

  TMyAIConsumerExtension = class
  private
    FChatPluginsList: TDictionary<Integer, IOTAAIPlugin>;
    FImageProcessorPluginList: TDictionary<Integer, IOTAAIPlugin>;
    FMyNotifier: TMyAIConsumerNotifier;
  public
    constructor Create;
    destructor Destroy; override;
    procedure DoChat(const AQuestion: string);
    procedure GenerateImage(const APrompt: string);
  end;

var
  FRequestIDList: TList<TGUID>;

implementation

{ TMyAIPlugin }

constructor TMyAIConsumerExtension.Create;
var
  I: Integer;
begin
  FChatPluginsList := TDictionary<Integer, IOTAAIPlugin>.Create;
  FImageProcessorPluginList := TDictionary<Integer, IOTAAIPlugin>.Create;
  FMyNotifier := TMyAIConsumerNotifier.Create;

  if AIEngineService.PluginCount > 0 then
  begin
    var LvPlugin: IOTAAIPlugin;
    var LNotifIndex: Integer;

    for I := 0 to Pred(AIEngineService.PluginCount) do
    begin
      LvPlugin := AIEngineService.GetPluginByIndex(I);
      if LvPlugin.Enabled then
      begin
        LNotifIndex := LvPlugin.AddNotifier(FMyNotifier);

        if afChat in LvPlugin.AvailableFeatures then
          FChatPluginsList.Add(LNotifIndex, LvPlugin);

        if afImageGeneration in LvPlugin.AvailableFeatures then
          FImageProcessorPluginList.Add(LNotifIndex, LvPlugin);

         // and so on
      end;
    end;
  end;
end;

destructor TMyAIConsumerExtension.Destroy;
begin
  for var Lindex in FChatPluginsList.Keys do
    FChatPluginsList.Items[Lindex].RemoveNotifier(Lindex);

  for var Lindex in FImageProcessorPluginList.Keys do
    FImageProcessorPluginList.Items[Lindex].RemoveNotifier(Lindex);

  FChatPluginsList.Free;
  FImageProcessorPluginList.Free;
  FMyNotifier.Free;

  inherited;
end;

procedure TMyAIConsumerExtension.GenerateImage(const APrompt: string);
begin
  if FImageProcessorPluginList.Count > 0 then
    FImageProcessorPluginList[0].GenerateImage(APrompt, '1024x1024', 'png');
end;

procedure TMyAIConsumerExtension.DoChat(const AQuestion: string);
begin
  if FChatPluginsList.Count > 0 then
  begin
    //Do something with One or more than one of the chat-supporting plugins
    FRequestIDList.Add(FChatPluginsList[0].Chat('Hello World!'));
    FRequestIDList.Add(FChatPluginsList[1].Chat('Hello Parallel World!'));

    // Or like the following
    for var LPlugin: IOTAAIPlugin in FChatPluginsList.Values do
      FRequestIDList.Add(LPlugin.Chat('Hello World!'));
  end;
end;

{ TMyAIConsumerNotifier }

procedure TMyAIConsumerNotifier.Answer(const AMessage: string; const ARequestID: TGUID);
begin
  if FRequestIDList.Contains(ARequestID) then
  begin
    // Do something with the Answer(AMessage)
    FRequestIDList.Remove(ARequestID);
  end;
end;

procedure TMyAIConsumerNotifier.Error(const AMessage: string; const ARequestID: TGUID);
begin
  if FRequestIDList.Contains(ARequestID) then
  begin
    // Do something with the Error(AMessage)
    FRequestIDList.Remove(ARequestID);
  end;
end;

procedure TMyAIConsumerNotifier.ImageLoaded(const AImage: TStream; const ARequestID: TGUID);
begin
  if FRequestIDList.Contains(ARequestID) then
  begin
    // Do something with image(AImage)
    FRequestIDList.Remove(ARequestID);
  end;
end;

procedure TMyAIConsumerNotifier.ImageLoaded(const A64BitImages: TArray<string>; const ARequestID: TGUID);
begin
 // Do something with image(A64BitImages)
end;

procedure TMyAIConsumerNotifier.ImageURlLoaded(const AImageURls: TArray<string>; const ARequestID: TGUID);
begin
 // Do something with image url(AImageURls)
end;

procedure TMyAIConsumerNotifier.ModelsLoaded(const AModels: TArray<string>; const ARequestID: TGUID);
begin
 // Do something with models list(AModels)
end;

procedure TMyAIConsumerNotifier.SpeechLoaded(const ASpeech: TStream; const ARequestID: TGUID);
begin
 // Do something with speech stream(ASpeech)
end;


initialization
  FRequestIDList := TList<TGUID>.Create;

finalization
  FRequestIDList.Free;

end.
