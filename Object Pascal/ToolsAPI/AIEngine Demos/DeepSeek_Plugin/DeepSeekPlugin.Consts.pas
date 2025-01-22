unit DeepSeekPlugin.Consts;

interface

const
  cDeepSeekAI_name = 'DeepSeek';
  cDeepSeekAI_def_BaseUrl = 'https://api.deepseek.com/v1/chat/completions';
  cDeepSeekAI_def_Model = 'deepseek-chat';
  cDeepSeekAI_Def_Timeout = 30000;

  cDeepSeekAI_Msg_CheckAPI = 'The API key has not been set.';
  cDeepSeekAI_Msg_NoAnswer = 'No Answer';

  cDeepSeekAI_RegKey = '\software\MyAIPlugins\DeepSeek';
  cDeepSeekAI_RegKey_Enabled = 'Enabled';
  cDeepSeekAI_RegKey_BaseURL = 'BaseURL';
  cDeepSeekAI_RegKey_Model = 'Model';
  cDeepSeekAI_RegKey_ApiKey = 'ApiKey';
  cDeepSeekAI_RegKey_Timeout = 'Timeout';

  cDeepSeekAI_Msg_BaseURL = 'Please Enter the BaseURL for DeepSeek';
  cDeepSeekAI_Msg_Model = 'Please Enter the Model for DeepSeek';
  cDeepSeekAI_Msg_APIKey = 'Please Enter the API Key for DeepSeek';
  cDeepSeekAI_Msg_Timeout = 'Please Enter the Timeout value for DeepSeek';
  cDeepSeekAI_URLRegex = '^((https?://[a-zA-Z0-9.-]+(:\d+)?(/.*)?)|(localhost(:\d+)?(/.*)?))$';
  cDeepSeekAI_Msg_InvalidURL = 'Invalid Base URL. Please provide a valid Localhost, HTTP or HTTPS URL.';

  cDeepSeekAI_ContentType = 'application/json';

  {
  Find DeepSeek API doc here: https://api-docs.deepseek.com
  Generate API Key here: https://platform.deepseek.com/api_keys
  }
implementation

end.
