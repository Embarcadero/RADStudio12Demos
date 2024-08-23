unit CoherePlugin.Consts;

interface

const
  cCohereAI_name = 'Cohere';
  cCohereAI_def_BaseUrl = 'https://api.cohere.com/v1/chat';
  cCohereAI_def_Model = 'command-r-plus';
  cCohereAI_Def_MaxTokens = 2048;
  cCohereAI_Def_Temp = 0.3;
  cCohereAI_Def_Timeout = 30000;

  cCohereAI_Msg_CheckAPI = 'The API key has not been set.';
  cCohereAI_Msg_NoAnswer = 'No Answer';

  cCohereAI_RegKey = '\software\MyAIPlugins\Cohere';
  cCohereAI_RegKey_Enabled = 'Enabled';
  cCohereAI_RegKey_BaseURL = 'BaseURL';
  cCohereAI_RegKey_Model = 'Model';
  cCohereAI_RegKey_ApiKey = 'ApiKey';
  cCohereAI_RegKey_MaxToken = 'MaxToken';
  cCohereAI_RegKey_Temperature = 'Temperature';
  cCohereAI_RegKey_Timeout = 'Timeout';

  cCohereAI_Msg_BaseURL = 'Please Enter the BaseURL for Cohere';
  cCohereAI_Msg_Model = 'Please Enter the Model for Cohere';
  cCohereAI_Msg_APIKey = 'Please Enter the API Key for Cohere';
  cCohereAI_Msg_MaxToken = 'Please Enter the MaxToken for Cohere';
  cCohereAI_Msg_Temperature = 'Please Enter the Temperature for Cohere';

  cCohereAI_Connector = 'web-search';
  cCohereAI_ContentType = 'application/json';
  {
  Find Cohere models here: https://docs.cohere.com/docs/models
  Genrate API Key here: https://dashboard.cohere.com/api-keys
  To extend this plugin, find API reference here : https://docs.cohere.com/reference
  Find Chat-Specific document: https://docs.cohere.com/reference/chat
  }
implementation

end.
