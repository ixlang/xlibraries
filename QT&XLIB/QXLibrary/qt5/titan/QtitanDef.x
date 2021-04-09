//xlang Source, Name:QtitanDef.x 
//Date: Mon Feb 19:14:19 2021 

package Qtitan{
    public enum SortOrder
    {
        SortNone,
        SortAscending,
        SortDescending
    };

    public enum ScrollBarsMode
    {
        ScrollNone,
        ScrollBoth,
        ScrollHorizontal,
        ScrollVertical,
        ScrollAuto
    };

    public enum LinesStyle
    {
        LinesNone = 0,
        LinesBoth,
        LinesBoth2D,
        LinesHorizontal,
        LinesHorizontal2D,
        LinesVertical,
        LinesVertical2D
    };

    public enum ScrollItemStyle
    {
        ScrollByItem,
        ScrollByPixel
    };

    public enum HighlightEffect
    {
        FlashEffect,
        AlphaEffect
    };

    public enum ItemPosition
    {
        AtNone = 0,
        AtBeginning,
        AtEnd
    };

    public enum LayoutArea
    {
        DefaultArea = 0,
        LeftArea,
        RightArea,
        TopArea,
        BottomArea
    };

    public enum BestFitModeFlag
    {
        FitToHeader = 1,
        FitToViewContent = 2,
        FitToContent = 4,
        FitToHeaderAndViewContent = FitToHeader | FitToViewContent,
        FitToHeaderAndContent = FitToHeader | FitToContent
    };
    
    public enum LayoutType
    {
        Split     = 1,
        Tabbed    = 2,
        AutoHide  = 3,
        Document  = 4
    };
    
   public  enum Theme
    {
        Blue,
        Dark,
        Light
    };
    
    public enum SelectionOperator
    {
        Empty = 0x0000,
        Clear = 0x0001,
        Select = 0x0002,
        Unselect = 0x0004,
        Invert = 0x0008,
        StartCurrent = 0x0010
    };

    public enum EditStrategy
    {
        OnFieldChange,
        OnRowChange
    };

    public enum IconApperance
    {
        IconInvisible = 0,
        IconOnly,
        IconAlignLeft,
        IconAlignRight
    };

    public enum ExpandingMode
    {
        Expanded = 0,
        Compact = 1,
        Minimal = 2,
        Popup = 3
    };

    public enum TransitionMode
    {
        Entrance,
        DrillIn,
        Suppress
    };

   public  enum ItemDataRoleEx 
    {
        ComboBoxRole = Qt.ItemDataRole.UserRole + 100,
        QueryIndexRole
    };

    public enum ContextColor
    {
        ContextColorNone,
        ContextColorGreen,
        ContextColorBlue,
        ContextColorRed,
        ContextColorYellow,
        ContextColorCyan,
        ContextColorPurple,
        ContextColorOrange
    };

    public enum DockPanelArea
    {
        NoDockPanelArea = 0x00,
        LeftDockPanelArea = 0x01,
        RightDockPanelArea = 0x02,
        TopDockPanelArea = 0x04,
        BottomDockPanelArea = 0x08,
        InsideDockPanelArea = 0x10,
        DockPanelArea_Mask = 0xff,
        AllDockPanelAreas = DockPanelArea_Mask
    };
 
    public enum DockBarArea // <-DockBarArea
    {
        DockBarNone = 0,
        DockBarLeft,
        DockBarRight,
        DockBarTop,
        DockBarBottom,
        DockBarFloat
    };
    
    public enum SysButtonKind
    {
        SysButtonHidden,
        SysMenuButton,
        BackButton
    };
    
    public enum WidgetAlign
    {
        AlignLeft,
        AlignRight,
        AlignClient
    };
    
    public enum DockPanelFeature 
    {
        DockPanelClosable   = 0x0001,
        DockPanelHideable   = 0x0002,
        DockPanelFloatable  = 0x0004,
        DockPaneNoCaption   = 0x0008,
        DockPanelMenuButton = 0x0010,

        DockPanelDockable   = 0x0020,
        DockPanelFloatableByTabDoubleClick = 0x0040,
        DockPanelFloatableByCaptionDoubleClick = 0x0080,
        DockPanelHoverShow = 0x0400,

        DockPanelFeatureMask = 0x0fff,
        AllDockPanelFeatures = DockPanelClosable | DockPanelHideable | DockPanelFloatable,
        NoDockPanelFeatures = 0x0000
    };
};