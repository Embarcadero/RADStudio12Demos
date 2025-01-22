unit DeepSeekPlugin.Models;

interface

uses
  DeepSeekPlugin.JsonHelper, System.Generics.Collections, REST.Json.Types;

{$M+}

type
  TMessages = class
  private
    [JSONName('content')]
    FContent: string;
    [JSONName('role')]
    FRole: string;
  published
    property Content: string read FContent write FContent;
    property Role: string read FRole write FRole;
  end;

  TRequestObj = class(TJsonReflectionBase)
  private
    [JSONName('messages'), JSONMarshalled(False)]
    FMessagesArray: TArray<TMessages>;
    [GenericListReflect]
    FMessages: TObjectList<TMessages>;
    [JSONName('model')]
    FModel: string;
    [JSONName('stream')]
    FStream: Boolean;
    function GetMessages: TObjectList<TMessages>;
  protected
    function GetAsJson: string; override;
  published
    property Messages: TObjectList<TMessages> read GetMessages;
    property Model: string read FModel write FModel;
    property Stream: Boolean read FStream write FStream;
  public
    constructor Create;
    destructor Destroy; override;
  end;

  TPromptTokensDetails = class
  private
    [JSONName('cached_tokens')]
    FCachedTokens: Integer;
  published
    property CachedTokens: Integer read FCachedTokens write FCachedTokens;
  end;

  TUsage = class
  private
    [JSONName('completion_tokens')]
    FCompletionTokens: Integer;
    [JSONName('prompt_cache_hit_tokens')]
    FPromptCacheHitTokens: Integer;
    [JSONName('prompt_cache_miss_tokens')]
    FPromptCacheMissTokens: Integer;
    [JSONName('prompt_tokens')]
    FPromptTokens: Integer;
    [JSONName('prompt_tokens_details')]
    FPromptTokensDetails: TPromptTokensDetails;
    [JSONName('total_tokens')]
    FTotalTokens: Integer;
  published
    property CompletionTokens: Integer read FCompletionTokens write FCompletionTokens;
    property PromptCacheHitTokens: Integer read FPromptCacheHitTokens write FPromptCacheHitTokens;
    property PromptCacheMissTokens: Integer read FPromptCacheMissTokens write FPromptCacheMissTokens;
    property PromptTokens: Integer read FPromptTokens write FPromptTokens;
    property PromptTokensDetails: TPromptTokensDetails read FPromptTokensDetails;
    property TotalTokens: Integer read FTotalTokens write FTotalTokens;
  public
    constructor Create;
    destructor Destroy; override;
  end;

  TMessage = class
  private
    [JSONName('content')]
    FContent: string;
    [JSONName('role')]
    FRole: string;
  published
    property Content: string read FContent write FContent;
    property Role: string read FRole write FRole;
  end;

  TChoices = class
  private
    [JSONName('finish_reason')]
    FFinishReason: string;
    [JSONName('index')]
    FIndex: Integer;
    [JSONName('logprobs')]
    FLogprobs: string;
    [JSONName('message')]
    FMessage: TMessage;
  published
    property FinishReason: string read FFinishReason write FFinishReason;
    property Index: Integer read FIndex write FIndex;
    property Logprobs: string read FLogprobs write FLogprobs;
    property Message: TMessage read FMessage;
  public
    constructor Create;
    destructor Destroy; override;
  end;

  TResponseObj = class(TJsonReflectionBase)
  private
    [JSONName('choices'), JSONMarshalled(False)]
    FChoicesArray: TArray<TChoices>;
    [GenericListReflect]
    FChoices: TObjectList<TChoices>;
    [JSONName('created')]
    FCreated: Integer;
    [JSONName('id')]
    FId: string;
    [JSONName('model')]
    FModel: string;
    [JSONName('object')]
    FObject: string;
    [JSONName('system_fingerprint')]
    FSystemFingerprint: string;
    [JSONName('usage')]
    FUsage: TUsage;
    function GetChoices: TObjectList<TChoices>;
  protected
    function GetAsJson: string; override;
  published
    property Choices: TObjectList<TChoices> read GetChoices;
    property Created: Integer read FCreated write FCreated;
    property Id: string read FId write FId;
    property Model: string read FModel write FModel;
    property &Object: string read FObject write FObject;
    property SystemFingerprint: string read FSystemFingerprint write FSystemFingerprint;
    property Usage: TUsage read FUsage;
  public
    constructor Create;
    destructor Destroy; override;
  end;

  TErrorItem = class
  private
    [JSONName('code')]
    FCode: string;
    [JSONName('message')]
    FMessage: string;
    [JSONName('param')]
    FParam: string;
    [JSONName('type')]
    FType: string;
  published
    property Code: string read FCode write FCode;
    property Message: string read FMessage write FMessage;
    property Param: string read FParam write FParam;
    property &Type: string read FType write FType;
  end;

  TErrorObj = class(TJsonReflectionBase)
  private
    [JSONName('error')]
    FError: TErrorItem;
  published
    property Error: TErrorItem read FError;
  public
    constructor Create;
    destructor Destroy; override;
  end;

implementation

{ TRequestObj }

constructor TRequestObj.Create;
begin
  inherited;
  FMessages := TObjectList<TMessages>.Create;
end;

destructor TRequestObj.Destroy;
begin
  GetMessages.Free;
  inherited;
end;

function TRequestObj.GetAsJson: string;
begin
  RefreshArray<TMessages>(FMessages, FMessagesArray);
  Result := inherited;
end;

function TRequestObj.GetMessages: TObjectList<TMessages>;
begin
  Result := ObjectList<TMessages>(FMessages, FMessagesArray);
end;

{ TUsage }

constructor TUsage.Create;
begin
  inherited;
  FPromptTokensDetails := TPromptTokensDetails.Create;
end;

destructor TUsage.Destroy;
begin
  FPromptTokensDetails.Free;
  inherited;
end;

{ TChoices }

constructor TChoices.Create;
begin
  inherited;
  FMessage := TMessage.Create;
end;

destructor TChoices.Destroy;
begin
  FMessage.Free;
  inherited;
end;

{ TResponseObj }

constructor TResponseObj.Create;
begin
  inherited;
  FUsage := TUsage.Create;
end;

destructor TResponseObj.Destroy;
begin
  FUsage.Free;
  GetChoices.Free;
  inherited;
end;

function TResponseObj.GetAsJson: string;
begin
  RefreshArray<TChoices>(FChoices, FChoicesArray);
  Result := inherited;
end;

function TResponseObj.GetChoices: TObjectList<TChoices>;
begin
  Result := ObjectList<TChoices>(FChoices, FChoicesArray);
end;

{ TErrorObj }

constructor TErrorObj.Create;
begin
  inherited;
  FError := TErrorItem.Create;
end;

destructor TErrorObj.Destroy;
begin
  FError.Free;
  inherited;
end;

end.
