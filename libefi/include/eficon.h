#ifndef _EFICON_INCLUDE_
#define _EFICON_INCLUDE_

// Text Attributes
#define EFI_BLACK                           0x00
#define EFI_BLUE                            0x01
#define EFI_GREEN                           0x02
#define EFI_CYAN                            0x03
#define EFI_RED                             0x04
#define EFI_MAGENTA                         0x05
#define EFI_BROWN                           0x06
#define EFI_LIGHTGRAY                       0x07
#define EFI_BRIGHT                          0x08
#define EFI_DARKGRAY                        EFI_BACK | EFI_BRIGHT
#define EFI_LIGHTBLUE                       0x09
#define EFI_LIGHTGREEN                      0x0A
#define EFI_LIGHTCYAN                       0x0B
#define EFI_LIGHTRED                        0x0C
#define EFI_LIGHTMAGENTA                    0x0D
#define EFI_YELLOW                          0x0E
#define EFI_WHITE                           0x0F

#define EFI_BACKGROUND_BLACK                0x00
#define EFI_BACKGROUND_BLUE                 0x10
#define EFI_BACKGROUND_GREEN                0x20
#define EFI_BACKGROUND_CYAN                 0x30
#define EFI_BACKGROUND_RED                  0x40
#define EFI_BACKGROUND_MAGENTA              0x50
#define EFI_BACKGROUND_BROWN                0x60
#define EFI_BACKGROUND_LIGHTGRAY            0x70

// Simple Input Protocol.
INTERFACE_DECL(_EFI_SIMPLE_TEXT_INPUT_PROTOCOL);

typedef struct
{
  UINT16  ScanCode;
  CHAR16  UnicodeChar;
} EFI_INPUT_KEY;

typedef EFI_STATUS
(EFIAPI *EFI_INPUT_RESET) 
(
  IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
  IN BOOLEAN                                  ExtendedVerification
);

typedef EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY) 
(
  IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
  OUT EFI_INPUT_KEY                         *Key
);

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL
{
  EFI_INPUT_RESET     Reset;
  EFI_INPUT_READ_KEY  ReadKeyStroke;
  EFI_EVENT           WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

// Simple Output Protocol.
INTERFACE_DECL(_EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_RESET)
(
  IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
  IN BOOLEAN                                  ExtendedVerification 
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_STRING)
(
  IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
  IN CHAR16                                   *String
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_TEST_STRING)
(
  IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
  IN CHAR16                                   *String
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_QUERY_MODE)
(
  IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
  IN UINTN                                    ModeNumber,
  OUT UINTN                                   *Columns,
  OUT UINTN                                   *Rows
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_MODE)
(
  IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
  IN UINTN                                    ModeNumber 
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_ATTRIBUTE)
(
  IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
  IN UINTN                                    Attribute
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_CLEAR_SCREEN)
(
  IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This 
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION)
(
  IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
  IN UINTN                            Column,
  IN UINTN                            Row 
);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_ENABLE_CURSOR)
(
  IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
  IN BOOLEAN                                  Visible 
);

typedef struct
{
  INT32   MaxMode;
  INT32   Mode;
  INT32   Attribute;
  INT32   CursorColumn;
  INT32   CursorRow;
  BOOLEAN CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
  EFI_TEXT_RESET                Reset;
  EFI_TEXT_STRING               OutputString;
  EFI_TEXT_TEST_STRING          TestString;
  EFI_TEXT_QUERY_MODE           QueryMode;
  EFI_TEXT_SET_MODE             SetMode;
  EFI_TEXT_SET_ATTRIBUTE        SetAttribute;
  EFI_TEXT_CLEAR_SCREEN         ClearScreen;
  EFI_TEXT_SET_CURSOR_POSITION  SetCursorPosition;
  EFI_TEXT_ENABLE_CURSOR        EnableCursor;
  SIMPLE_TEXT_OUTPUT_MODE       *Mode;         
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

#endif
