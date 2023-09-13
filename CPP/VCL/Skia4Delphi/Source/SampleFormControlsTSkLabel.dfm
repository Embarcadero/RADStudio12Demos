inherited frmTSkLabel: TfrmTSkLabel
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
            Caption = 'TSkLabel'
          end>
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 356
        ExplicitHeight = 43
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
      object pnlMultiStyle: TPanel
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
        OnClick = pnlMultiStyleClick
        ExplicitWidth = 308
        DesignSize = (
          312
          50)
        object lblMultiStyleDescription: TSkLabel
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
          OnClick = pnlMultiStyleClick
          TextSettings.Font.Size = 11.000000000000000000
          TextSettings.FontColor = xFFA0A0A1
          TextSettings.MaxLines = 1
          Words = <
            item
              Caption = 'A single label with multiples colors and sizes'
            end>
          ExplicitTop = 26
          ExplicitWidth = 303
        end
        object lblMultiStyleTitle: TSkLabel
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
          OnClick = pnlMultiStyleClick
          TextSettings.Font.Weight = Medium
          TextSettings.FontColor = xFF1B1B1B
          TextSettings.MaxLines = 2
          Words = <
            item
              Caption = 'Multiple Styles'
            end>
          ExplicitWidth = 303
        end
        object svgMultiStyleArrow: TSkSvg
          Left = 287
          Top = 17
          Width = 16
          Height = 16
          Anchors = [akTop, akRight]
          OnClick = pnlMultiStyleClick
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
        object pnlMultiStyleLine: TPanel
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
      object pnlRTL: TPanel
        AlignWithMargins = True
        Left = 20
        Top = 121
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
        OnClick = pnlRTLClick
        ExplicitWidth = 308
        DesignSize = (
          312
          50)
        object lblRTLDescription: TSkLabel
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
          OnClick = pnlRTLClick
          TextSettings.Font.Size = 11.000000000000000000
          TextSettings.FontColor = xFFA0A0A1
          TextSettings.MaxLines = 1
          Words = <
            item
              Caption = 'Example with Persian text, RTL language'
            end>
          ExplicitTop = 26
          ExplicitWidth = 303
        end
        object lblRTLTitle: TSkLabel
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
          OnClick = pnlRTLClick
          TextSettings.Font.Weight = Medium
          TextSettings.FontColor = xFF1B1B1B
          TextSettings.MaxLines = 2
          Words = <
            item
              Caption = 'Right-to-left'
            end>
          ExplicitWidth = 303
        end
        object svgRTLArrow: TSkSvg
          Left = 299
          Top = 17
          Width = 16
          Height = 16
          Anchors = [akTop, akRight]
          OnClick = pnlRTLClick
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
        object pnlRTLLine: TPanel
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
      object pnlFontWeight: TPanel
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
        TabOrder = 2
        OnClick = pnlFontWeightClick
        ExplicitWidth = 308
        DesignSize = (
          312
          50)
        object lblFontWeightDescription: TSkLabel
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
          OnClick = pnlFontWeightClick
          TextSettings.Font.Size = 11.000000000000000000
          TextSettings.FontColor = xFFA0A0A1
          TextSettings.MaxLines = 1
          Words = <
            item
              Caption = 'Several lineweight options in addition to bold and regular'
            end>
          ExplicitTop = 26
          ExplicitWidth = 303
        end
        object lblFontWeightTitle: TSkLabel
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
          OnClick = pnlFontWeightClick
          TextSettings.Font.Weight = Medium
          TextSettings.FontColor = xFF1B1B1B
          TextSettings.MaxLines = 2
          Words = <
            item
              Caption = 'Font Weight'
            end>
          ExplicitWidth = 303
        end
        object svgFontWeightArrow: TSkSvg
          Left = 299
          Top = 17
          Width = 16
          Height = 16
          Anchors = [akTop, akRight]
          OnClick = pnlFontWeightClick
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
        object pnlFontWeightLine: TPanel
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
      object pnlMaxLines: TPanel
        AlignWithMargins = True
        Left = 20
        Top = 171
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
        TabOrder = 3
        OnClick = pnlMaxLinesClick
        ExplicitWidth = 308
        DesignSize = (
          312
          50)
        object lblMaxLinesDescription: TSkLabel
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
          OnClick = pnlMaxLinesClick
          TextSettings.Font.Size = 11.000000000000000000
          TextSettings.FontColor = xFFA0A0A1
          TextSettings.MaxLines = 1
          Words = <
            item
              Caption = 'Controlling maximum number of lines'
            end>
          ExplicitTop = 26
          ExplicitWidth = 303
        end
        object lblMaxLinesTitle: TSkLabel
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
          OnClick = pnlMaxLinesClick
          TextSettings.Font.Weight = Medium
          TextSettings.FontColor = xFF1B1B1B
          TextSettings.MaxLines = 2
          Words = <
            item
              Caption = 'Maximum Lines'
            end>
          ExplicitWidth = 303
        end
        object svgMaxLinesArrow: TSkSvg
          Left = 299
          Top = 17
          Width = 16
          Height = 16
          Anchors = [akTop, akRight]
          OnClick = pnlMaxLinesClick
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
        object pnlMaxLinesLine: TPanel
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
      object pnlWordOnClickEvent: TPanel
        AlignWithMargins = True
        Left = 20
        Top = 221
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
        TabOrder = 4
        OnClick = pnlWordOnClickEventClick
        ExplicitWidth = 308
        DesignSize = (
          312
          50)
        object lblWordOnClickEventDescription: TSkLabel
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
          OnClick = pnlWordOnClickEventClick
          TextSettings.Font.Size = 11.000000000000000000
          TextSettings.FontColor = xFFA0A0A1
          TextSettings.MaxLines = 1
          Words = <
            item
              Caption = 'Example of text with clickable region'
            end>
          ExplicitTop = 26
          ExplicitWidth = 303
        end
        object lblWordOnClickEventTitle: TSkLabel
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
          OnClick = pnlWordOnClickEventClick
          TextSettings.Font.Weight = Medium
          TextSettings.FontColor = xFF1B1B1B
          TextSettings.MaxLines = 2
          Words = <
            item
              Caption = 'Word OnClick Event'
            end>
          ExplicitWidth = 303
        end
        object svgWordOnClickEventArrow: TSkSvg
          Left = 299
          Top = 17
          Width = 16
          Height = 16
          Anchors = [akTop, akRight]
          OnClick = pnlWordOnClickEventClick
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
        object pnlWordOnClickEventLine: TPanel
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
      object pnlFamiliesFallbacks: TPanel
        AlignWithMargins = True
        Left = 20
        Top = 271
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
        TabOrder = 5
        OnClick = pnlFamiliesFallbacksClick
        ExplicitWidth = 308
        DesignSize = (
          312
          50)
        object lblFamiliesFallbacksDescription: TSkLabel
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
          OnClick = pnlFamiliesFallbacksClick
          TextSettings.Font.Size = 11.000000000000000000
          TextSettings.FontColor = xFFA0A0A1
          TextSettings.MaxLines = 1
          Words = <
            item
              Caption = 'Use multiple families like in CSS, first available will be used'
            end>
          ExplicitTop = 26
          ExplicitWidth = 303
        end
        object lblFamiliesFallbacksTitle: TSkLabel
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
          OnClick = pnlFamiliesFallbacksClick
          TextSettings.Font.Weight = Medium
          TextSettings.FontColor = xFF1B1B1B
          TextSettings.MaxLines = 2
          Words = <
            item
              Caption = 'Families Fallbacks'
            end>
          ExplicitWidth = 303
        end
        object svgFamiliesFallbacksArrow: TSkSvg
          Left = 299
          Top = 17
          Width = 16
          Height = 16
          Anchors = [akTop, akRight]
          OnClick = pnlFamiliesFallbacksClick
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
        object pnlFamiliesFallbacksLine: TPanel
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
      object pnlJustifiedText: TPanel
        AlignWithMargins = True
        Left = 20
        Top = 371
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
        TabOrder = 6
        OnClick = pnlJustifiedTextClick
        ExplicitWidth = 308
        DesignSize = (
          312
          50)
        object lblJustifiedTextDescription: TSkLabel
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
          OnClick = pnlJustifiedTextClick
          TextSettings.Font.Size = 11.000000000000000000
          TextSettings.FontColor = xFFA0A0A1
          TextSettings.MaxLines = 1
          Words = <
            item
              Caption = 'Learn how to justify a text horizontally'
            end>
          ExplicitTop = 26
          ExplicitWidth = 303
        end
        object lblJustifiedTextTitle: TSkLabel
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
          OnClick = pnlJustifiedTextClick
          TextSettings.Font.Weight = Medium
          TextSettings.FontColor = xFF1B1B1B
          TextSettings.MaxLines = 2
          Words = <
            item
              Caption = 'Justified Text'
            end>
          ExplicitWidth = 303
        end
        object svgJustifiedTextArrow: TSkSvg
          Left = 299
          Top = 17
          Width = 16
          Height = 16
          Anchors = [akTop, akRight]
          OnClick = pnlJustifiedTextClick
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
        object pnlJustifiedTextLine: TPanel
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
      object pnlCustomFontFamily: TPanel
        AlignWithMargins = True
        Left = 20
        Top = 321
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
        TabOrder = 7
        OnClick = pnlCustomFontFamilyClick
        ExplicitWidth = 308
        DesignSize = (
          312
          50)
        object lblCustomFontFamilyDescription: TSkLabel
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
          OnClick = pnlCustomFontFamilyClick
          TextSettings.Font.Size = 11.000000000000000000
          TextSettings.FontColor = xFFA0A0A1
          TextSettings.MaxLines = 1
          Words = <
            item
              Caption = 'Use custom font without install it in the machine'
            end>
          ExplicitTop = 26
          ExplicitWidth = 303
        end
        object lblCustomFontFamilyTitle: TSkLabel
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
          OnClick = pnlCustomFontFamilyClick
          TextSettings.Font.Weight = Medium
          TextSettings.FontColor = xFF1B1B1B
          TextSettings.MaxLines = 2
          Words = <
            item
              Caption = 'Custom Font Family'
            end>
          ExplicitWidth = 303
        end
        object svgCustomFontFamilyArrow: TSkSvg
          Left = 299
          Top = 17
          Width = 16
          Height = 16
          Anchors = [akTop, akRight]
          OnClick = pnlCustomFontFamilyClick
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
        object pnlCustomFontFamilyLine: TPanel
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
