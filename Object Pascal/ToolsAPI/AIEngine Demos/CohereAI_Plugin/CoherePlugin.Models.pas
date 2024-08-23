unit CoherePlugin.Models;

interface

uses
  CoherePlugin.JsonHelper, System.Generics.Collections, REST.Json.Types;

{$M+}

type
  TDocuments = class(TDictionary<string, string>)
  end;

  TTokens = class
  private
    [JSONName('input_tokens')]
    FInputTokens: Integer;
    [JSONName('output_tokens')]
    FOutputTokens: Integer;
  published
    property InputTokens: Integer read FInputTokens write FInputTokens;
    property OutputTokens: Integer read FOutputTokens write FOutputTokens;
  end;

  TBilledUnits = class
  private
    [JSONName('input_tokens')]
    FInputTokens: Integer;
    [JSONName('output_tokens')]
    FOutputTokens: Integer;
  published
    property InputTokens: Integer read FInputTokens write FInputTokens;
    property OutputTokens: Integer read FOutputTokens write FOutputTokens;
  end;

  TApiVersion = class
  private
    [JSONName('version')]
    FVersion: string;
  published
    property Version: string read FVersion write FVersion;
  end;

  TMeta = class
  private
    [JSONName('api_version')]
    FApiVersion: TApiVersion;
    [JSONName('billed_units')]
    FBilledUnits: TBilledUnits;
    [JSONName('tokens')]
    FTokens: TTokens;
  published
    property ApiVersion: TApiVersion read FApiVersion;
    property BilledUnits: TBilledUnits read FBilledUnits;
    property Tokens: TTokens read FTokens;
  public
    constructor Create;
    destructor Destroy; override;
  end;

  TChatHistory = class
  private
    [JSONName('message')]
    FMessage: string;
    [JSONName('role')]
    FRole: string;
  published
    property Message: string read FMessage write FMessage;
    property Role: string read FRole write FRole;
  end;

  TResponseObj = class(TJsonReflectionBase)
  private
    [JSONName('chat_history'), JSONMarshalled(False)]
    FChatHistoryArray: TArray<TChatHistory>;
    [GenericListReflect]
    FChatHistory: TObjectList<TChatHistory>;
    [JSONName('documents'), JSONMarshalled(False)]
    FDocumentsArray: TArray<TDocuments>;
    [GenericListReflect]
    FDocuments: TObjectList<TDocuments>;
    [JSONName('finish_reason')]
    FFinishReason: string;
    [JSONName('generation_id')]
    FGenerationId: string;
    [JSONName('meta')]
    FMeta: TMeta;
    [JSONName('response_id')]
    FResponseId: string;
    [JSONName('text')]
    FText: string;
    function GetChatHistory: TObjectList<TChatHistory>;
    function GetDocuments: TObjectList<TDocuments>;
  protected
    function GetAsJson: string; override;
  published
    property ChatHistory: TObjectList<TChatHistory> read GetChatHistory;
    property Documents: TObjectList<TDocuments> read GetDocuments;
    property FinishReason: string read FFinishReason write FFinishReason;
    property GenerationId: string read FGenerationId write FGenerationId;
    property Meta: TMeta read FMeta;
    property ResponseId: string read FResponseId write FResponseId;
    property Text: string read FText write FText;
  public
    constructor Create;
    destructor Destroy; override;
  end;

  TError = class(TJsonReflectionBase)
  private
    [JSONName('message')]
    FMessage: string;
  published
    property Message: string read FMessage write FMessage;
  end;

  // Response-related types
  TConnectors = class
  private
    [JSONName('id')]
    FId: string;
  published
    property Id: string read FId write FId;
  end;

  TRequestObj = class(TJsonReflectionBase)
  private
    [JSONName('message')]
    FMessage: string;
    [JSONName('model')]
    FModel: string;
    [JSONName('temperature')]
    FTemperature: Double;
    [JSONName('max_tokens')]
    FMax_Token: Integer;
    [JSONName('connectors'), JSONMarshalled(False)]
    FConnectorsArray: TArray<TConnectors>;
    [GenericListReflect]
    FConnectors: TObjectList<TConnectors>;
    function GetConnectors: TObjectList<TConnectors>;
  protected
    function GetAsJson: string; override;
  published
    property Connectors: TObjectList<TConnectors> read GetConnectors;
    property Message: string read FMessage write FMessage;
    property Model: string read FModel write FModel;
    property Temperature: Double read FTemperature write FTemperature;
    property Max_Token: Integer read FMax_Token write FMax_Token;
  public
    destructor Destroy; override;
  end;

implementation

{ TMeta }

constructor TMeta.Create;
begin
  inherited;
  FApiVersion := TApiVersion.Create;
  FBilledUnits := TBilledUnits.Create;
  FTokens := TTokens.Create;
end;

destructor TMeta.Destroy;
begin
  FApiVersion.Free;
  FBilledUnits.Free;
  FTokens.Free;
  inherited;
end;

{ TResponse }

constructor TResponseObj.Create;
begin
  inherited;
  FMeta := TMeta.Create;
end;

destructor TResponseObj.Destroy;
begin
  FMeta.Free;
  GetChatHistory.Free;
  GetDocuments.Free;
  inherited;
end;

function TResponseObj.GetChatHistory: TObjectList<TChatHistory>;
begin
  Result := ObjectList<TChatHistory>(FChatHistory, FChatHistoryArray);
end;

function TResponseObj.GetDocuments: TObjectList<TDocuments>;
begin
  Result := ObjectList<TDocuments>(FDocuments, FDocumentsArray);
end;

function TResponseObj.GetAsJson: string;
begin
  RefreshArray<TChatHistory>(FChatHistory, FChatHistoryArray);
  RefreshArray<TDocuments>(FDocuments, FDocumentsArray);
  Result := inherited;
end;

{ TRequestObj }

destructor TRequestObj.Destroy;
begin
  GetConnectors.Free;
  inherited;
end;

function TRequestObj.GetAsJson: string;
begin
  RefreshArray<TConnectors>(FConnectors, FConnectorsArray);
  Result := inherited;
end;

function TRequestObj.GetConnectors: TObjectList<TConnectors>;
begin
  Result := ObjectList<TConnectors>(FConnectors, FConnectorsArray);
end;

end.
