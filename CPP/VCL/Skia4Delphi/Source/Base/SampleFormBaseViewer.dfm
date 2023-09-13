inherited frmBaseViewer: TfrmBaseViewer
  ClientHeight = 573
  ClientWidth = 331
  OnClose = FormClose
  OnDestroy = FormDestroy
  ExplicitWidth = 347
  ExplicitHeight = 612
  TextHeight = 15
  inherited pnlContent: TPanel
    Width = 331
    Height = 573
    ExplicitWidth = 347
    ExplicitHeight = 577
    inherited pnlTitle: TPanel
      Width = 351
      ExplicitWidth = 347
      inherited lblTitle: TSkLabel
        Width = 351
        Words = <
          item
            Caption = 'Base Viewer'
          end>
        ExplicitWidth = 351
      end
      inherited pnlTitleLine: TPanel
        Width = 351
        ExplicitWidth = 347
      end
    end
    inherited sbxContent: TScrollBox
      Width = 351
      Height = 500
      DoubleBuffered = True
      Padding.Top = 0
      ParentBackground = False
      ParentDoubleBuffered = False
      ExplicitWidth = 347
      ExplicitHeight = 499
    end
    inherited pnlTip: TPanel
      Top = 544
      Width = 351
      ExplicitTop = 543
      ExplicitWidth = 347
      inherited pnlTipLine: TPanel
        Width = 351
        ExplicitWidth = 347
      end
      inherited pnlTipContent: TPanel
        Width = 286
        ExplicitWidth = 282
        inherited lblTipDescription: TSkLabel
          Width = 286
          ExplicitWidth = 286
        end
      end
    end
  end
end
