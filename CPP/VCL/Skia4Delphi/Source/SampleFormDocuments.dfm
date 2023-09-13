inherited frmDocuments: TfrmDocuments
  ClientWidth = 352
  ExplicitWidth = 364
  ExplicitHeight = 641
  TextHeight = 15
  inherited pnlContent: TPanel
    Width = 352
    ExplicitWidth = 348
    ExplicitHeight = 602
    inherited pnlTitle: TPanel
      Width = 352
      ExplicitWidth = 348
      inherited lblTitle: TSkLabel
        Width = 352
        Words = <
          item
            Caption = 'Documents'
          end>
      end
      inherited pnlTitleLine: TPanel
        Width = 352
        ExplicitWidth = 348
      end
    end
    inherited sbxContent: TScrollBox
      Width = 352
      ExplicitWidth = 348
      ExplicitHeight = 524
      object pnlCreatePDFDrawingSVG: TPanel
        AlignWithMargins = True
        Left = 20
        Top = 21
        Width = 312
        Height = 50
        Cursor = crHandPoint
        Margins.Left = 20
        Margins.Top = 0
        Margins.Right = 20
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        Font.Charset = DEFAULT_CHARSET
        Font.Color = 15134704
        Font.Height = -12
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentColor = True
        ParentFont = False
        ShowCaption = False
        TabOrder = 0
        OnClick = pnlCreatePDFDrawingSVGClick
        ExplicitWidth = 308
        DesignSize = (
          312
          50)
        object lblCreatePDFDrawingSVGDescription: TSkLabel
          AlignWithMargins = True
          Left = 0
          Top = 25
          Width = 296
          Height = 15
          Margins.Left = 0
          Margins.Top = 0
          Margins.Right = 16
          Margins.Bottom = 0
          Align = alTop
          OnClick = pnlCreatePDFDrawingSVGClick
          TextSettings.Font.Size = 11.000000000000000000
          TextSettings.FontColor = xFFA0A0A1
          TextSettings.MaxLines = 1
          Words = <
            item
              Caption = 'Create a PDF document and draw one SVG inside it'
            end>
          ExplicitTop = 26
          ExplicitWidth = 303
        end
        object lblCreatePDFDrawingSVGTitle: TSkLabel
          AlignWithMargins = True
          Left = 0
          Top = 6
          Width = 296
          Height = 19
          Margins.Left = 0
          Margins.Top = 6
          Margins.Right = 16
          Margins.Bottom = 0
          Align = alTop
          OnClick = pnlCreatePDFDrawingSVGClick
          TextSettings.Font.Weight = Medium
          TextSettings.FontColor = xFF1B1B1B
          TextSettings.MaxLines = 2
          Words = <
            item
              Caption = 'Create a PDF drawing a SVG'
            end>
          ExplicitWidth = 303
        end
        object svgCreatePDFDrawingSVGArrow: TSkSvg
          Left = 295
          Top = 17
          Width = 16
          Height = 16
          Anchors = [akTop, akRight]
          OnClick = pnlCreatePDFDrawingSVGClick
          Svg.Source = 
            '<?xml version="1.0" encoding="iso-8859-1"?>'#13#10'<!-- Generator: Ado' +
            'be Illustrator 19.0.0, SVG Export Plug-In . SVG Version: 6.00 Bu' +
            'ild 0)  -->'#13#10'<svg version="1.1" id="Capa_1" xmlns="http://www.w3' +
            '.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px' +
            '" y="0px"'#13#10#9' viewBox="0 0 47.255 47.255" style="enable-backgroun' +
            'd:new 0 0 47.255 47.255;" xml:space="preserve">'#13#10'<g>'#13#10#9'<path d="' +
            'M12.314,47.255c-0.256,0-0.512-0.098-0.707-0.293c-0.391-0.391-0.3' +
            '91-1.023,0-1.414l21.92-21.92l-21.92-21.92'#13#10#9#9'c-0.391-0.391-0.391' +
            '-1.023,0-1.414s1.023-0.391,1.414,0L35.648,22.92c0.391,0.391,0.39' +
            '1,1.023,0,1.414L13.021,46.962'#13#10#9#9'C12.825,47.157,12.57,47.255,12.' +
            '314,47.255z"/>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>' +
            #13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</' +
            'g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'</svg' +
            '>'
          ExplicitLeft = 298
        end
        object pnlCreatePDFDrawingSVGLine: TPanel
          Left = 0
          Top = 49
          Width = 312
          Height = 1
          Align = alBottom
          BevelOuter = bvNone
          Color = 15132908
          ParentBackground = False
          TabOrder = 0
          StyleElements = [seFont, seBorder]
          ExplicitWidth = 308
        end
      end
      object pnlCreateXPSDrawingSVG: TPanel
        AlignWithMargins = True
        Left = 20
        Top = 71
        Width = 312
        Height = 50
        Cursor = crHandPoint
        Margins.Left = 20
        Margins.Top = 0
        Margins.Right = 20
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        Font.Charset = DEFAULT_CHARSET
        Font.Color = 15134704
        Font.Height = -12
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentColor = True
        ParentFont = False
        ShowCaption = False
        TabOrder = 1
        OnClick = pnlCreateXPSDrawingSVGClick
        ExplicitWidth = 308
        DesignSize = (
          312
          50)
        object lblCreateXPSDrawingSVGDescription: TSkLabel
          AlignWithMargins = True
          Left = 0
          Top = 25
          Width = 296
          Height = 15
          Margins.Left = 0
          Margins.Top = 0
          Margins.Right = 16
          Margins.Bottom = 0
          Align = alTop
          OnClick = pnlCreateXPSDrawingSVGClick
          TextSettings.Font.Size = 11.000000000000000000
          TextSettings.FontColor = xFFA0A0A1
          TextSettings.MaxLines = 1
          Words = <
            item
              Caption = 'Create a XPS document and draw one SVG inside it'
            end>
          ExplicitTop = 26
          ExplicitWidth = 303
        end
        object lblCreateXPSDrawingSVGTitle: TSkLabel
          AlignWithMargins = True
          Left = 0
          Top = 6
          Width = 296
          Height = 19
          Margins.Left = 0
          Margins.Top = 6
          Margins.Right = 16
          Margins.Bottom = 0
          Align = alTop
          OnClick = pnlCreateXPSDrawingSVGClick
          TextSettings.Font.Weight = Medium
          TextSettings.FontColor = xFF1B1B1B
          TextSettings.MaxLines = 2
          Words = <
            item
              Caption = 'Create a XPS drawing a SVG'
            end>
          ExplicitWidth = 303
        end
        object svgCreateXPSDrawingSVGArrow: TSkSvg
          Left = 299
          Top = 17
          Width = 16
          Height = 16
          Anchors = [akTop, akRight]
          OnClick = pnlCreateXPSDrawingSVGClick
          Svg.Source = 
            '<?xml version="1.0" encoding="iso-8859-1"?>'#13#10'<!-- Generator: Ado' +
            'be Illustrator 19.0.0, SVG Export Plug-In . SVG Version: 6.00 Bu' +
            'ild 0)  -->'#13#10'<svg version="1.1" id="Capa_1" xmlns="http://www.w3' +
            '.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px' +
            '" y="0px"'#13#10#9' viewBox="0 0 47.255 47.255" style="enable-backgroun' +
            'd:new 0 0 47.255 47.255;" xml:space="preserve">'#13#10'<g>'#13#10#9'<path d="' +
            'M12.314,47.255c-0.256,0-0.512-0.098-0.707-0.293c-0.391-0.391-0.3' +
            '91-1.023,0-1.414l21.92-21.92l-21.92-21.92'#13#10#9#9'c-0.391-0.391-0.391' +
            '-1.023,0-1.414s1.023-0.391,1.414,0L35.648,22.92c0.391,0.391,0.39' +
            '1,1.023,0,1.414L13.021,46.962'#13#10#9#9'C12.825,47.157,12.57,47.255,12.' +
            '314,47.255z"/>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>' +
            #13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</' +
            'g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'<g>'#13#10'</g>'#13#10'</svg' +
            '>'
          ExplicitLeft = 298
        end
        object pnlCreateXPSDrawingSVGLine: TPanel
          Left = 0
          Top = 49
          Width = 312
          Height = 1
          Align = alBottom
          BevelOuter = bvNone
          Color = 15132908
          ParentBackground = False
          TabOrder = 0
          StyleElements = [seFont, seBorder]
          ExplicitWidth = 308
        end
      end
    end
    inherited pnlTip: TPanel
      Width = 352
      ExplicitTop = 568
      ExplicitWidth = 348
      inherited pnlTipLine: TPanel
        Width = 352
        ExplicitWidth = 348
      end
      inherited pnlTipContent: TPanel
        Width = 287
        ExplicitWidth = 283
        inherited lblTipDescription: TSkLabel
          Width = 287
        end
      end
    end
  end
end
