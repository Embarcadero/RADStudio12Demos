//---------------------------------------------------------------------------
// Copyright (c) 2016 Embarcadero Technologies, Inc. All rights reserved.
//
// This software is the copyrighted property of Embarcadero Technologies, Inc.
// ("Embarcadero") and its licensors. You may only use this software if you
// are an authorized licensee of Delphi, C++Builder or RAD Studio
// (the "Embarcadero Products").  This software is subject to Embarcadero's
// standard software license and support agreement that accompanied your
// purchase of the Embarcadero Products and is considered a Redistributable,
// as such term is defined thereunder. Your use of this software constitutes
// your acknowledgement of your agreement to the foregoing software license
// and support agreement.
//---------------------------------------------------------------------------
unit APIDocDelphiAttributesUnitConsts;

interface

resourcestring

  sError = 'Error';
  sErrorMessage = 'errormessage';
  sDescription = 'description';
  sNotFound = 'Not Found';
  sUnExpectedToken ='Unexpected Token, expected string';
  sPathItem = 'PathItem';
  sPostedData = 'PostedData';

const
  cYamlDefinitions = '''
  #
   ItemObject:
      type: object
      properties:
        RowID:
          type: integer
        Original:
          type: object
          properties:
           EMP_NO:
            type: integer
           FIRST_NAME:
            type: string
           LAST_NAME:
            type: string
           PHONE_EXT:
            type: string
           HIRE_DATE:
            type: string
           DEPT_NO:
            type: string
           JOB_CODE:
            type: string
           JOB_GRADE:
            type: integer
           JOB_COUNTRY:
            type: string
           SALARY:
            type: integer
           FULL_NAME:
            type: string
  #
   TableObject:
      type: object
      properties:
        class:
          type: string
        Name:
          type: string
        SourceName:
          type: string
        SourceID:
          type: integer
        RowList:
          type: array
          items:
           $ref: "#/definitions/ItemObject"
  #
   EmployeeTable:
      type: object
      properties:
        FBDS:
         type: object
         properties:
           Version:
             type: string
           Manager:
             type: object
             properties:
               TableList:
                type: array
                items:
                 $ref: "#/definitions/TableObject"
  #
   PostObject:
     properties:
      EMP_NO:
       type: integer
      FIRST_NAME:
       type: string
      LAST_NAME:
       type: string
      PHONE_EXT:
       type: string
      HIRE_DATE:
       type: string
       format: date-time
      DEPT_NO:
       type: string
      JOB_CODE:
       type: string
      JOB_GRADE:
       type: integer
      JOB_COUNTRY:
       type: string
      SALARY:
       type: integer
      FULL_NAME:
       type: string
  #
   PutObject:
     properties:
      EMP_NO:
       type: integer
      FIRST_NAME:
       type: string
      LAST_NAME:
       type: string
      PHONE_EXT:
       type: string
      HIRE_DATE:
       type: string
       format: date-time
      DEPT_NO:
       type: string
      JOB_CODE:
       type: string
      JOB_GRADE:
       type: integer
      JOB_COUNTRY:
       type: string
      SALARY:
       type: integer
      FULL_NAME:
       type: string
  #
   ItemPostedResponseObject:
      type: object
      properties:
        PostedData:
          type: array
          items:
           type: string
  #
   ItemPutResponseObject:
      type: object
      properties:
        PathItem:
          type: string
        PostedData:
          type: array
          items:
           type: string

  ''';

cJSONDefinitions = '''
  {
      "ItemObject": {
          "type": "object",
          "properties": {
              "RowID": {
                  "type": "integer"
              },
              "Original": {
                  "type": "object",
                  "properties": {
                      "EMP_NO": {
                          "type": "integer"
                      },
                      "FIRST_NAME": {
                          "type": "string"
                      },
                      "LAST_NAME": {
                         "type": "string"
                     },
                     "PHONE_EXT": {
                         "type": "string"
                     },
                     "HIRE_DATE": {
                         "type": "string"
                     },
                     "DEPT_NO": {
                         "type": "string"
                     },
                     "JOB_CODE": {
                         "type": "string"
                     },
                     "JOB_GRADE": {
                         "type": "integer"
                     },
                     "JOB_COUNTRY": {
                         "type": "string"
                     },
                     "SALARY": {
                         "type": "integer"
                     },
                     "FULL_NAME": {
                        "type": "string"
                     }
                 }
            }
         }
     },
     "TableObject": {
         "type": "object",
         "properties": {
             "class": {
                 "type": "string"
             },
             "Name": {
                 "type": "string"
             },
             "SourceName": {
                 "type": "string"
             },
             "SourceID": {
                 "type": "integer"
             },
             "RowList": {
                 "type": "array",
                 "items": {
                     "$ref": "#/definitions/ItemObject"
                 }
             }
        }
     },
     "EmployeeTable": {
         "type": "object",
         "properties": {
            "FBDS": {
                 "type": "object",
                 "properties": {
                     "Version": {
                         "type": "string"
                     },
                     "Manager": {
                         "type": "object",
                         "properties": {
                             "TableList": {
                                 "type": "array",
                                 "items": {
                                     "$ref": "#/definitions/TableObject"
                                 }
                             }
                         }
                     }
                 }
             }
         }
     },
     "PostObject": {
         "properties": {
             "EMP_NO": {
                 "type": "integer"
             },
             "FIRST_NAME": {
                 "type": "string"
             },
             "LAST_NAME": {
                 "type": "string"
             },
             "PHONE_EXT": {
                 "type": "string"
             },
             "HIRE_DATE": {
                 "type": "string",
                 "format": "date-time"
             },
             "DEPT_NO": {
                 "type": "string"
             },
             "JOB_CODE": {
                 "type": "string"
             },
             "JOB_GRADE": {
                 "type": "integer"
             },
              "JOB_COUNTRY": {
                  "type": "string"
              },
              "SALARY": {
                  "type": "integer"
              },
              "FULL_NAME": {
                  "type": "string"
              }
          }
      },
     "PutObject": {
         "properties": {
             "EMP_NO": {
                 "type": "integer"
             },
             "FIRST_NAME": {
                 "type": "string"
             },
             "LAST_NAME": {
                 "type": "string"
             },
             "PHONE_EXT": {
                 "type": "string"
             },
             "HIRE_DATE": {
                 "type": "string",
                 "format": "date-time"
             },
             "DEPT_NO": {
                 "type": "string"
             },
             "JOB_CODE": {
                 "type": "string"
             },
             "JOB_GRADE": {
                 "type": "integer"
             },
              "JOB_COUNTRY": {
                  "type": "string"
              },
              "SALARY": {
                  "type": "integer"
              },
              "FULL_NAME": {
                  "type": "string"
              }
          }
      },
      "ItemPostedResponseObject": {
          "type": "object",
          "properties": {
              "PostedData": {
                  "type": "array",
                  "items": {
                      "type": "string"
                  }
              }
          }
      },
      "ItemPutResponseObject": {
          "type": "object",
          "properties": {
              "PathItem": {
                  "type": "string"
              },
              "PostedData": {
                  "type": "array",
                  "items": {
                      "type": "string"
                  }
              }
          }
      }
  }
  ''';

implementation


end.
