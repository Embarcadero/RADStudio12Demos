//---------------------------------------------------------------------------

// This software is Copyright (c) 2015 Embarcadero Technologies, Inc.
// You may only use this software if you are an authorized licensee
// of an Embarcadero developer tools product.
// This software is considered a Redistributable as defined under
// the software license agreement that comes with the Embarcadero Products
// and is subject to that software license agreement.

//---------------------------------------------------------------------------

unit MusicPlayer.Android;

interface
{$IFDEF ANDROID}
uses
  FMX.Graphics,
  MusicPlayer.Utils,
  System.IoUtils, System.SysUtils, System.Classes,
  FMX.Types, FMX.Platform.Android, FMX.Helpers.Android,
  Androidapi.JNI.Os, Androidapi.JNI.Net,
  Androidapi.JNIBridge, Androidapi.JNI.JavaTypes, Androidapi.JNI.GraphicsContentViewText,
  Androidapi.JNI.Media, Androidapi.JNI.Provider, Androidapi.Helpers, Androidapi.JNI.App;
type
  TMusicPlayer = class
  private
  type
    TProcessThread = class (TThread)
    private
      [weak] FMusicPlayer: TMusicPlayer;
      FOnProcessPlay: TOnProcessPlayEvent;
      procedure DoProcessPlay;
    public
      constructor Create(CreateSuspended: Boolean; AMusicPlayer: TMusicPlayer; processHandler: TOnProcessPlayEvent);
      destructor Destroy; override;
      procedure Execute; override;
    end;
  protected
    class var FInstance: TMusicPlayer;
  private
    FCurrentIndex: Integer;
    FPlaylist: TArray<TMPSong>;
    FAlbums: TArray<TMPAlbum>;
    FMusicPlayer: JMediaPlayer;
    FPlayBackState: TMPPlaybackState;
    FRepeatMode: TMPRepeatMode;
    FShuffleMode: Boolean;
    FDefaultAlbumImage: TBitmap;
    FOnSongChange: TOnSongChangeEvent;
    FOnProcessPlay: TOnProcessPlayEvent;
    constructor Create(AType: TMPControllerType = TMPControllerType.App);
    procedure DoOnSongChange(newIndex: Integer);
    procedure DoOnProcessPlay(newPos: Single);
    procedure SetVolume(const Value: Single);
    procedure SetTime(const Value: Single);
    procedure SetRepeatMode(const Value: TMPRepeatMode);
    procedure SetShuffleMode(const Value: Boolean);
    function GetVolume: Single;
    function GetTime: Single;
    function GetRepeatMode: TMPRepeatMode;
    function GetDuration: Single;
    function GetPlaybackState: TMPPlaybackState;
    function GetShuffleMode: Boolean;
  public
    destructor Destroy; override;
    class procedure SetPlayerType(AType: TMPControllerType);
    class function DefaultPlayer: TMusicPlayer;
    property CurrentIndex: Integer read FCurrentIndex;
    property Volume: Single read GetVolume write SetVolume;
    property Time: Single read GetTime write SetTime;
    property Duration: Single read GetDuration;
    property PlaybackState: TMPPlaybackState read GetPlaybackState;
    property ShuffleMode: Boolean read GetShuffleMode write SetShuffleMode;
    property RepeatMode: TMPRepeatMode read GetRepeatMode write SetRepeatMode;
    property Playlist: TArray<TMPSong> read FPlaylist;
    property Albums: TArray<TMPAlbum> read FAlbums;
    property DefaultAlbumImage: TBitmap read FDefaultAlbumImage write FDefaultAlbumImage;
    property OnSongChange: TOnSongChangeEvent read FOnSongChange write FOnSongChange;
    property OnProcessPlay: TOnProcessPlayEvent read FOnProcessPlay write FOnProcessPlay;
    function GetAlbums: TArray<string>;
    function GetSongs: TArray<string>;
    function GetSongsInAlbum(AName: string): TArray<string>;
    function IsPlaying: Boolean;
    function CanSkipBack: Boolean;
    function CanSkipForward: Boolean;
    procedure PlaySong(path: string);
    procedure PlayByIndex(Index: Integer);
    procedure Play;
    procedure Stop;
    procedure Pause;
    procedure Next;
    procedure Previous;
  end;
var
  NoArtBitmap: TBitmap;
{$ENDIF}
implementation
{$IFDEF ANDROID}
{ TMusicPlayer }

function TMusicPlayer.CanSkipBack: Boolean;
begin
  Result := (Length(FPlaylist) > 0) and (FCurrentIndex > 0) and
    (FPlayBackState in [TMPPlaybackState.Playing, TMPPlaybackState.Paused]);
end;

function TMusicPlayer.CanSkipForward: Boolean;
var
  Len: Integer;
begin
  Result := False;
  Len := Length(FPlaylist);
  if (Len = 0) or not (FPlayBackState in [TMPPlaybackState.Playing, TMPPlaybackState.Paused]) then
    Exit(Result);

  case RepeatMode of
    TMPRepeatMode.One:
      Result := (FCurrentIndex >= 0) and (FCurrentIndex < Len);
    TMPRepeatMode.Default,
    TMPRepeatMode.None:
      Result := (FCurrentIndex >= 0) and (FCurrentIndex < Len - 1);
    TMPRepeatMode.All:
      Result := True;
  end;
end;

constructor TMusicPlayer.Create(AType: TMPControllerType);
begin
  MainActivity.setVolumeControlStream(TJAudioManager.JavaClass.STREAM_MUSIC);
  FMusicPlayer := TJMediaPlayer.Create;
  FPlayBackState := TMPPlaybackState.Stopped;
  FRepeatMode := TMPRepeatMode.All;
  FShuffleMode := False;
  FDefaultAlbumImage := TBitmap.CreateFromFile(TPath.Combine(TPath.GetDocumentsPath,'MusicNote.png'));
  TProcessThread.Create(True,self,DoOnProcessPlay).Start;
end;

class function TMusicPlayer.DefaultPlayer: TMusicPlayer;
begin
  if not Assigned(FInstance) then
    FInstance := TMusicPlayer.Create;
  Result := FInstance;
end;

destructor TMusicPlayer.Destroy;
begin
  FMusicPlayer.release;
end;

procedure TMusicPlayer.DoOnSongChange(newIndex: Integer);
begin
  if Assigned(FOnSongChange) then
    TThread.Queue(TThread.CurrentThread, procedure
      begin
        FOnSongChange(newIndex);
      end);
end;

procedure TMusicPlayer.DoOnProcessPlay(newPos: Single);
begin
  if Assigned(FOnProcessPlay) then
    TThread.Queue(TThread.CurrentThread, procedure
      begin
        FOnProcessPlay(newPos);
      end);
end;

function TMusicPlayer.GetAlbums: TArray<string>;
var
  Projection: TJavaObjectArray<JString>;
  Cursor: JCursor;
  ArtPath: String;
  TmpPath: String;
begin
  Projection := CreateJavaStringArray([TJAudio_AlbumColumns.JavaClass.ALBUM, TJAudio_AlbumColumns.JavaClass.ARTIST, '_id',
    TJAudio_AlbumColumns.JavaClass.ALBUM_ART]);

  try
    Cursor := TAndroidHelper.ContentResolver.query(TJAudio_Albums.JavaClass.EXTERNAL_CONTENT_URI, Projection, nil, nil, nil);

    if Cursor <> nil then
      try
        SetLength(Result, Cursor.getCount);
        SetLength(FAlbums, Cursor.getCount + 1);

        FAlbums[Cursor.getCount] := TMPAlbum.AllMusicAlbum;

        while Cursor.moveToNext do
        begin
          FAlbums[Cursor.getPosition].Name := JStringToString(Cursor.getString(0));
          FAlbums[Cursor.getPosition].Artist := JStringToString(Cursor.getString(1));
          FAlbums[Cursor.getPosition].Album_ID := Cursor.getInt(2);

          ArtPath := JStringToString(Cursor.getString(3));

          if TFile.Exists(ArtPath) then
          begin
            try
              //Workaround for loading problems: copy to a file with correct extension.
              TmpPath := System.IOUtils.TPath.Combine(System.IOUtils.TPath.GetDocumentsPath,  'tmp.jpg');

              TFile.Copy(ArtPath, TmpPath);

              FAlbums[Cursor.getPosition].Artwork := TBitmap.CreateFromFile(TmpPath);

              TFile.Delete(TmpPath);
            except
            end;
          end
          else
            FAlbums[Cursor.getPosition].Artwork := FDefaultAlbumImage;

          Result[Cursor.getPosition] := FAlbums[Cursor.getPosition].Name;
        end;
      finally
        Cursor.close;
      end;
  finally
    Projection.Free;
  end;
end;

function TMusicPlayer.GetDuration: Single;
begin
  Result := FMusicPlayer.getDuration;
end;

function TMusicPlayer.GetPlaybackState: TMPPlaybackState;
begin
  Result := FPlayBackState;
end;

function TMusicPlayer.GetRepeatMode: TMPRepeatMode;
begin
  Result := FRepeatMode;
end;

function TMusicPlayer.GetShuffleMode: Boolean;
begin
  Result := FShuffleMode;
end;

function TMusicPlayer.GetSongs: TArray<string>;
var
  Selection: JString;
  Projection: TJavaObjectArray<JString>;
  Cursor: JCursor;
begin
  Selection := StringToJString(JStringToString(TJAudio_AudioColumns.JavaClass.IS_MUSIC) + ' != 0');

  Projection := CreateJavaStringArray([TJAudio_AudioColumns.JavaClass.ARTIST, 'title', '_data', TJAudio_AudioColumns.JavaClass.ALBUM,
    TJAudio_AudioColumns.JavaClass.DURATION]);

  try
    Cursor := TAndroidHelper.ContentResolver.query(TJAudio_Media.JavaClass.EXTERNAL_CONTENT_URI, Projection, Selection, nil, nil);

    if Cursor <> nil then
      try
        SetLength(Result, Cursor.getCount);
        SetLength(FPlaylist, Cursor.getCount);

        while Cursor.moveToNext do
        begin
          FPlaylist[Cursor.getPosition] := TMPSong.FromCursor(Cursor);
          Result[Cursor.getPosition] := Format('[%s]-[%s]', [FPlaylist[Cursor.getPosition].Artist, FPlaylist[Cursor.getPosition].Title]);
        end;
      finally
        Cursor.close;
      end;
  finally
    Projection.Free;
  end;
end;

function TMusicPlayer.GetSongsInAlbum(AName: string): TArray<string>;
var
  Selection: JString;
  Projection: TJavaObjectArray<JString>;
  SelectionArgs: TJavaObjectArray<JString>;
  Cursor: JCursor;
begin
  if AName = TMPAlbum.AllMusicAlbum.Name then
  begin
    Result := GetSongs;
    Exit;
  end;

  Selection := StringToJString(JStringToString(TJAudio_AudioColumns.JavaClass.IS_MUSIC) + ' != 0 and ' +
    JStringToString(TJAudio_AudioColumns.JavaClass.ALBUM) + ' = ?');

  Projection := CreateJavaStringArray([TJAudio_AudioColumns.JavaClass.ARTIST, 'title', '_data', TJAudio_AudioColumns.JavaClass.ALBUM,
    TJAudio_AudioColumns.JavaClass.DURATION]);

  try
    SelectionArgs := CreateJavaStringArray([AName]);

    try
      Cursor := TAndroidHelper.ContentResolver.query(TJAudio_Media.JavaClass.EXTERNAL_CONTENT_URI, Projection, Selection, SelectionArgs, nil);

      if Cursor <> nil then
        try
          SetLength(Result, Cursor.getCount);
          SetLength(FPlaylist, Cursor.getCount);

          while Cursor.moveToNext do
          begin
            FPlaylist[Cursor.getPosition] := TMPSong.FromCursor(Cursor);
            Result[Cursor.getPosition] := Format('[%s]-[%s]', [FPlaylist[Cursor.getPosition].Artist, FPlaylist[Cursor.getPosition].Title]);
          end;
        finally
          Cursor.close;
        end;
    finally
      SelectionArgs.Free;
    end;
  finally
    Projection.Free
  end;
end;

function TMusicPlayer.GetTime: Single;
begin
  Result := FMusicPlayer.getCurrentPosition;
end;

function TMusicPlayer.GetVolume: Single;
var
  AudioManager: JAudioManager;
begin
  AudioManager := TJAudioManager.Wrap(MainActivity.getSystemService(TJContext.JavaClass.AUDIO_SERVICE));
  Result := AudioManager.getStreamVolume(TJAudioManager.JavaClass.STREAM_MUSIC);
  Result := Result / AudioManager.getStreamMaxVolume(TJAudioManager.JavaClass.STREAM_MUSIC);
end;

procedure TMusicPlayer.Next;
begin
  case RepeatMode of
    TMPRepeatMode.One:
    begin
      Time := 0;
      Play;
    end;
    TMPRepeatMode.Default,
    TMPRepeatMode.None:
      if CurrentIndex = Length(FPlaylist) - 1  then
        FMusicPlayer.Stop
      else
      begin
        if ShuffleMode then
          PlayByIndex(Random(Length(FPlaylist)))
        else
          PlayByIndex(FCurrentIndex + 1);
      end;
    TMPRepeatMode.All:
      if FCurrentIndex = Length(FPlaylist) - 1 then
        PlayByIndex(0)
      else
      begin
        if FShuffleMode then
          PlayByIndex(Random(Length(FPlaylist)))
        else
          PlayByIndex(FCurrentIndex + 1);
      end;
  end;
  DoOnSongChange(FCurrentIndex);
end;

procedure TMusicPlayer.Pause;
begin
  FMusicPlayer.pause;
  FPlayBackState := TMPPlaybackState.Paused;
end;

procedure TMusicPlayer.Play;
begin
  if FPlayBackState = TMPPlaybackState.Stopped  then
    FMusicPlayer.prepare;
  FMusicPlayer.start;
  FPlayBackState := TMPPlaybackState.Playing;
end;

procedure TMusicPlayer.PlayByIndex(Index: Integer);
begin
  FCurrentIndex := Index;
  PlaySong(FPlaylist[FCurrentIndex].Path);
end;

function TMusicPlayer.IsPlaying: Boolean;
begin
  Result := FMusicPlayer.isPlaying;
end;

procedure TMusicPlayer.PlaySong(path: string);
begin
  Stop;
  FMusicPlayer.reset;
  FMusicPlayer.setDataSource(StringToJString(path));
  Play;
end;

procedure TMusicPlayer.Previous;
begin
  if (FCurrentIndex > 0) and (FCurrentIndex < Length(FPlaylist)) then
  begin
    PlayByIndex(FCurrentIndex -1);
    DoOnSongChange(FCurrentIndex);
  end;
end;

class procedure TMusicPlayer.SetPlayerType(AType: TMPControllerType);
begin
  // Do nothing
end;

procedure TMusicPlayer.SetRepeatMode(const Value: TMPRepeatMode);
begin
  FRepeatMode := Value;
end;

procedure TMusicPlayer.SetShuffleMode(const Value: Boolean);
begin
  FShuffleMode := Value;
end;

procedure TMusicPlayer.SetTime(const Value: Single);
begin
  FMusicPlayer.seekTo(Trunc(Value));
end;

procedure TMusicPlayer.SetVolume(const Value: Single);
var
  AudioManager: JAudioManager;
begin
  AudioManager := TJAudioManager.Wrap(MainActivity.getSystemService(TJContext.JavaClass.AUDIO_SERVICE));
  AudioManager.setStreamVolume(TJAudioManager.JavaClass.STREAM_MUSIC,
    Round(AudioManager.getStreamMaxVolume(TJAudioManager.JavaClass.STREAM_MUSIC) * Value), 0);
end;

procedure TMusicPlayer.Stop;
begin
  if FPlayBackState in [TMPPlaybackState.Playing, TMPPlaybackState.Paused] then
    FMusicPlayer.seekTo(0);
  FPlayBackState := TMPPlaybackState.Stopped;
  FMusicPlayer.stop;
  while FMusicPlayer.isPlaying do
    sleep(10);
  DoOnProcessPlay(0);
end;

{ TMusicPlayer.TProcessThread }

constructor TMusicPlayer.TProcessThread.Create(CreateSuspended: Boolean;
  AMusicPlayer: TMusicPlayer; processHandler: TOnProcessPlayEvent);
begin
  inherited Create(CreateSuspended);
  FOnProcessPlay := processHandler;
  FMusicPlayer := AMusicPlayer;
end;

destructor TMusicPlayer.TProcessThread.Destroy;
begin
  FMusicPlayer := nil;
  inherited;
end;

procedure TMusicPlayer.TProcessThread.Execute;
begin
  inherited;
  while Assigned(FMusicPlayer) do
  begin
    case FMusicPlayer.PlaybackState of
      Playing: DoProcessPlay;
      Stopped,
      Paused,
      Interrupted,
      SeekingForward,
      SeekingBackward: sleep(200);
    end;
  end;
end;

procedure TMusicPlayer.TProcessThread.DoProcessPlay;
var
  currentPos: Single;
begin
  currentPos := FMusicPlayer.Time;
  if Assigned(FOnProcessPlay) then
    FOnProcessPlay((currentPos/FMusicPlayer.Duration) * 100);


  if FMusicPlayer.IsPlaying then
    Sleep(200)
  else
    FMusicPlayer.Next;


end;
{$ENDIF}
end.
