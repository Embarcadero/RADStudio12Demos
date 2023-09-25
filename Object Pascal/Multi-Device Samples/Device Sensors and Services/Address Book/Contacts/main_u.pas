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
unit main_u;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes,
  System.Variants, System.Permissions,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Graphics, FMX.Dialogs,
  FMX.AddressBook.Types, FMX.AddressBook, FMX.StdCtrls, FMX.SearchBox,
  FMX.Layouts, FMX.ListBox, FMX.Controls.Presentation, FMX.Edit, FMX.TabControl,
  FMX.Platform, System.Actions, FMX.ActnList, FMX.ListView.Types,
  FMX.ListView.Appearances, FMX.ListView.Adapters.Base, FMX.ListView,
  FMX.StdActns, FMX.MediaLibrary.Actions, FMX.Objects, FMX.Surfaces;

type
  TForm1 = class(TForm)
    TabControl1: TTabControl;
    TabItemContact: TTabItem;
    edtFirstName: TEdit;
    edtLastName: TEdit;
    edtWorkMail: TEdit;
    btnOK: TButton;
    btnClear: TButton;
    TabItemContacts: TTabItem;
    ToolBar1: TToolBar;
    btnRemove: TSpeedButton;
    btnRefresh: TSpeedButton;
    TabItemGroup: TTabItem;
    edtGroupName: TEdit;
    btnAddGroup: TButton;
    btnRemoveGroup: TButton;
    AddressBook1: TAddressBook;
    ActionList1: TActionList;
    ActionAddContact: TAction;
    ActionRefresh: TAction;
    ActionRemoveGroup: TAction;
    ActionAddGroup: TAction;
    ActionRemoveContact: TAction;
    ToolBar2: TToolBar;
    ToolBar3: TToolBar;
    Label7: TLabel;
    Label8: TLabel;
    Label1: TLabel;
    ContactList: TListBox;
    ContactInfoHeader: TListBoxGroupHeader;
    FirstName: TListBoxItem;
    LastName: TListBoxItem;
    WorkEmail: TListBoxItem;
    Group: TListBoxItem;
    ComboBox1: TComboBox;
    ListBox1: TListBox;
    ListBoxGroupHeader1: TListBoxGroupHeader;
    EnterGroup: TListBoxItem;
    SelectGroup: TListBoxItem;
    ComboBox2: TComboBox;
    ListBoxGroupHeader2: TListBoxGroupHeader;
    ListViewContacts: TListView;
    Photo: TListBoxItem;
    btnLoadPicture: TButton;
    Image1: TImage;
    TakePhotoFromLibraryAction1: TTakePhotoFromLibraryAction;
    btnTakePicture: TButton;
    TakePhotoFromCameraAction1: TTakePhotoFromCameraAction;
    procedure FormShow(Sender: TObject);
    procedure AddressBook1PermissionRequest(ASender: TObject;
      const AMessage: string; const AAccessGranted: Boolean);
    procedure btnClearClick(Sender: TObject);
    procedure AddressBook1ExternalChange(ASender: TObject);
    procedure ActionAddContactExecute(Sender: TObject);
    procedure ActionRefreshExecute(Sender: TObject);
    procedure ActionList1Update(Action: TBasicAction; var Handled: Boolean);
    procedure ActionRemoveGroupExecute(Sender: TObject);
    procedure ActionAddGroupExecute(Sender: TObject);
    procedure ActionRemoveContactExecute(Sender: TObject);
    procedure TakePhotoFromLibraryAction1DidFinishTaking(Image: TBitmap);
    procedure TakePhotoFromCameraAction1DidFinishTaking(Image: TBitmap);
    procedure btnTakePictureClick(Sender: TObject);
  private
    { Private declarations }
    FDefaultSource: TAddressBookSource;
    FGroups: TAddressBookGroups;
    procedure FillGroupComboBox(const AGroups: TAddressBookGroups;
      const AComboBox: TComboBox);
    procedure FillGroupList(Source: TAddressBookSource);
    procedure FillContactList(Source: TAddressBookSource);
    procedure AddListViewItem(Contact: TAddressBookContact);
    procedure DeleteContact(const AKey: TModalResult);
    procedure ClearAddContactForm;
    procedure DisplayRationale(Sender: TObject; const APermissions: TClassicStringDynArray; const APostRationaleProc: TProc);
    procedure TakePicturePermissionRequestResult(Sender: TObject; const APermissions: TClassicStringDynArray; const AGrantResults: TClassicPermissionStatusDynArray);
  end;

var
  Form1: TForm1;

implementation

uses
{$IFDEF ANDROID}
  Androidapi.Helpers,
  Androidapi.JNI.JavaTypes,
  Androidapi.JNI.Os,
{$ENDIF}
  System.Math, FMX.DialogService;

{$R *.fmx}
{$R *.iPhone47in.fmx IOS}

// Update the contact and group list after external changes
procedure TForm1.AddressBook1ExternalChange(ASender: TObject);
begin
  AddressBook1.RevertCurrentChangesAndUpdate;
  ActionRefresh.Execute;
end;

// --------------------------------------------------------------------
// Request a permission to access Address Book
procedure TForm1.AddressBook1PermissionRequest(ASender: TObject;
  const AMessage: string; const AAccessGranted: Boolean);
begin
  if AAccessGranted then
    ActionRefresh.Execute
  else
    ShowMessage('You have no access to Address Book. Reason: ' + AMessage);
end;

// --------------------------------------------------------------------
// Clear the Add New Contact form.
procedure TForm1.ClearAddContactForm;
begin
  edtFirstName.Text := '';
  edtLastName.Text := '';
  edtWorkMail.Text := '';
  ComboBox1.ItemIndex := -1;
  Image1.Bitmap.SetSize(0, 0);
end;

// --------------------------------------------------------------------
// Clear the Add New Contact form.
procedure TForm1.btnClearClick(Sender: TObject);
begin
  ClearAddContactForm;
end;

procedure TForm1.btnTakePictureClick(Sender: TObject);
var
  StoragePermission: string;
begin
  if TOSVersion.Check(11) then
    TakePhotoFromCameraAction1.Execute
  else
  begin
    StoragePermission := JStringToString(TJManifest_permission.JavaClass.WRITE_EXTERNAL_STORAGE);
    PermissionsService.RequestPermissions([StoragePermission], TakePicturePermissionRequestResult);
  end;
end;

// --------------------------------------------------------------------
// Remove the selected contact from Address Book
// The apps executes this procedure only if the user confirmed the contact deletion
procedure TForm1.DeleteContact(const AKey: TModalResult);
var
  ContactIndex, ContactID: Integer;
  Contact: TAddressBookContact;
begin
  if AKey = System.UITypes.mrYes then
  begin
    ContactIndex := ListViewContacts.ItemIndex;
    if ContactIndex > -1 then
    begin
      ContactID := ListViewContacts.Items[ContactIndex].Tag;
      Contact := AddressBook1.ContactByID(ContactID);
      try
        try
          AddressBook1.RemoveContact(Contact);
          ListViewContacts.Items.Delete(ContactIndex);
        except
          on E: EAddressBookException do
            ShowMessage('Cannot delete the contact');
        end;
      finally
        Contact.Free;
      end;
    end;
  end;
end;

// Optional rationale display routine to display permission requirement rationale to the user
procedure TForm1.DisplayRationale(Sender: TObject; const APermissions: TClassicStringDynArray; const APostRationaleProc: TProc);
begin
  // Show an explanation to the user *asynchronously* - don't block this thread waiting for the user's response!
  // After the user sees the explanation, invoke the post-rationale routine to request the permissions
  TDialogService.ShowMessage('The application needs to have access to the address book',
    procedure(const AResult: TModalResult)
    begin
      APostRationaleProc
    end)
end;
// --------------------------------------------------------------------

procedure TForm1.FormShow(Sender: TObject);
begin
  // Display this information box while loading the contacts
  if AddressBook1.Supported then
    ShowMessage('Loading contacts...')
  else
    ShowMessage('This platform does not support the Address Book service');
  AddressBook1.RequestPermission(DisplayRationale);
  TabControl1.ActiveTab := TabItemContacts;
end;

procedure TForm1.TakePicturePermissionRequestResult(Sender: TObject; const APermissions: TClassicStringDynArray; const AGrantResults: TClassicPermissionStatusDynArray);
begin
  // 1 permission involved: WRITE_EXTERNAL_STORAGE
  if (Length(AGrantResults) = 1) and (AGrantResults[0] = TPermissionStatus.Granted) then
    TakePhotoFromCameraAction1.Execute
  else
    ShowMessage('Cannot take a photo because the required permission has not been granted')
end;

procedure TForm1.TakePhotoFromCameraAction1DidFinishTaking(Image: TBitmap);
begin
  Image1.Bitmap.Assign(Image);
end;

procedure TForm1.TakePhotoFromLibraryAction1DidFinishTaking(Image: TBitmap);
begin
  Image1.Bitmap.Assign(Image);
end;

// --------------------------------------------------------------------
// Fill the group list
procedure TForm1.FillGroupComboBox(const AGroups: TAddressBookGroups;
  const AComboBox: TComboBox);
var
  I: Integer;
begin
  AComboBox.Clear;
  AComboBox.BeginUpdate;
  try
    for I := 0 to AGroups.Count - 1 do
      AComboBox.Items.Add(FGroups.Items[I].Name);
  finally
    AComboBox.EndUpdate;
  end;
  AComboBox.Visible := AGroups.Count > 0;
end;

procedure TForm1.FillGroupList(Source: TAddressBookSource);
begin
  FGroups := TAddressBookGroups.Create;
  AddressBook1.AllGroups(Source, FGroups);

  FillGroupComboBox(FGroups, ComboBox1);
  FillGroupComboBox(FGroups, ComboBox2);
end;

// --------------------------------------------------------------------
// Add a new item to List box
procedure TForm1.ActionAddContactExecute(Sender: TObject);
var
  Contact: TAddressBookContact;
  Photo: TBitmapSurface;
  eMails: TContactEmails;
begin
  Contact := nil;
  Photo := nil;
  eMails := nil;

  try
    try
      Contact := AddressBook1.CreateContact(FDefaultSource);
      Contact.FirstName := edtFirstName.Text;
      Contact.LastName := edtLastName.Text;

      if not Image1.Bitmap.IsEmpty then
      begin
        Photo := TBitmapSurface.Create;
        Photo.Assign(Image1.Bitmap);
        Contact.Photo := Photo;
        Image1.Bitmap.SetSize(0, 0);
      end;

      // Add the work mail
      eMails := TContactEmails.Create;
      eMails.AddEmail(TContactEmail.TLabelKind.Work, edtWorkMail.Text);
      Contact.eMails := eMails;

      // Save a newly created contact to Address Book
      AddressBook1.SaveContact(Contact);
    except
      on E: EAddressBookException do
      begin
        ShowMessage('Cannot add the contact');
        Exit;
      end;
    end;

    try
      // Add the contact to the selected group, if any
      if InRange(ComboBox1.ItemIndex, 0, FGroups.Count - 1) then
        AddressBook1.AddContactIntoGroup(FGroups.Items[ComboBox1.ItemIndex], Contact);

      AddListViewItem(Contact);
      TabControl1.ActiveTab := TabItemContacts;
    except
      on E: EAddressBookException do
        ShowMessage('Cannot add the contact into the group');
    end;
  finally
    Contact.Free;
    Photo.Free;
    eMails.Free;
  end;

  // Clear the Add Contact Form
  ClearAddContactForm;
end;

// Add a new group
procedure TForm1.ActionAddGroupExecute(Sender: TObject);
var
  Group: TAddressBookGroup;
begin
  Group := nil;

  try
    try
      Group := AddressBook1.CreateGroup(FDefaultSource);
      Group.Name := edtGroupName.Text;
      AddressBook1.SaveGroup(Group);
      edtGroupName.Text := '';
      TabControl1.ActiveTab := TabItemContacts;
      FillGroupList(FDefaultSource);
    except
      on E: EAddressBookException do
        ShowMessage('Cannot add the group');
    end;
  finally
    Group.Free;
  end;
end;

// The Action list methods
procedure TForm1.ActionList1Update(Action: TBasicAction; var Handled: Boolean);
begin
  ActionAddContact.Enabled := AddressBook1.Supported and
    ((edtFirstName.Text <> '') or (edtLastName.Text <> ''));
  ActionRefresh.Enabled := AddressBook1.Supported;
  ActionAddGroup.Enabled := AddressBook1.Supported;
  ActionRemoveGroup.Visible := (FGroups <> nil) and (FGroups.Count > 0);
  ActionRemoveContact.Enabled := ListViewContacts.ItemIndex > -1;
end;

procedure TForm1.ActionRefreshExecute(Sender: TObject);
begin
  try
    FDefaultSource := AddressBook1.DefaultSource;
    FillGroupList(FDefaultSource);
    FillContactList(FDefaultSource);
  except
    on E: EAddressBookException do
      ShowMessage('Cannot get the groups and contacts');
  end;
end;

procedure TForm1.ActionRemoveContactExecute(Sender: TObject);
begin
  TDialogService.MessageDialog('Do you want to delete this contact?',
    TMsgDlgType.mtConfirmation, mbYesNo, TMsgDlgBtn.mbNo, 0, DeleteContact);
end;

procedure TForm1.ActionRemoveGroupExecute(Sender: TObject);
begin
  if (ComboBox2.ItemIndex > -1) and (ComboBox2.ItemIndex < FGroups.Count) then
  begin
    try
      AddressBook1.RemoveGroup(FGroups.Items[ComboBox2.ItemIndex]);
      FillGroupList(FDefaultSource);
    except
      on E: Exception do
        ShowMessage('Cannot remove the group');
    end;
  end;
end;

// Add a new item to the contact list
procedure TForm1.AddListViewItem(Contact: TAddressBookContact);
var
  ListViewItem: TListViewItem;
begin
  ListViewItem := ListViewContacts.Items.Add;
  ListViewItem.Text := Contact.DisplayName;
  ListViewItem.Tag := Contact.ID;
end;

// --------------------------------------------------------------------
// Fill the contact list
procedure TForm1.FillContactList(Source: TAddressBookSource);
var
  I: Integer;
  Contacts: TAddressBookContacts;
begin
  Contacts := TAddressBookContacts.Create;
  try
    AddressBook1.AllContacts(Source, Contacts);
    ListViewContacts.BeginUpdate;
    try
      ListViewContacts.Items.Clear;
      for I := 0 to Contacts.Count - 1 do
        AddListViewItem(Contacts.Items[I]);
    finally
      ListViewContacts.EndUpdate;
    end;
  finally
    Contacts.Free;
  end;
end;

// ---------------------------------------------------------------------------
end.
