//xlang Source, Name:qt5/widgets/QHeaderView.x 
//Date: Wed Jan 17:34:24 2021 
package Qt{
    public class QHeaderView : QWidget{

        public QHeaderView(long h){
            super(h);
        }
        
        public Orientation orientation() {
            return (Orientation)QtXnl.widget_get_int_value(nativehandle, Constant.QH_ORIENTATION);
        }
        
        public int offset() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_GETOFFSET);
        }
        
        public int length() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_GETLENGTH);
        }
        
                
        public int sectionSizeHint(int logicalIndex) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_SECTIONSIZEHINT, logicalIndex, 0);
        }

        public int visualIndexAt(int position) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_VISUALINDEXAT, position, 0);
        }
        
        public int logicalIndexAt(int position) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_LOGICALINDEXAT, position, 0);
        }

        public int logicalIndexAt(int x, int y) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_LOGICALINDEXATXY, x, y);
        }
        
        public int logicalIndexAt(QPoint pos) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_LOGICALINDEXATXY, pos.x, pos.y);
        }

        public int sectionSize(int logicalIndex) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_SECTIONSIZE, logicalIndex, 0);
        }
        
        public int sectionPosition(int logicalIndex) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_SECTIONPOSITION, logicalIndex, 0);
        }
        
        public int sectionViewportPosition(int logicalIndex) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_SECTIONVIEWPORTPOSITION, logicalIndex, 0);
        }

        public void moveSection(int from, int to){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_MOVESECTION, from, to);
        }
        
        public void swapSections(int first, int second){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_SWAPSECTIONS, first, second);
        }
        
        public void resizeSection(int logicalIndex, int size){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_RESIZESECTION, logicalIndex, size);
        }
        
        public void resizeSections(ResizeMode mode){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QH_RESIZESECTIONS, mode);
        }

        public bool isSectionHidden(int logicalIndex) {
            return 0 != QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_ISSECTIONHIDDEN, logicalIndex, 0);
        }
        
        public void setSectionHidden(int logicalIndex, bool hide){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_SETSECTIONHIDDEN, logicalIndex, hide ? 1 : 0);
        }
        
        public int hiddenSectionCount() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_HIDDENSECTIONCOUNT);
        }

        public void hideSection(int logicalIndex){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QH_HIDESECTION, logicalIndex);
        }
        
        public void showSection(int logicalIndex){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QH_SHOWSECTION, logicalIndex);
        }

        public int count() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_COUNT);
        }
        
        public int visualIndex(int logicalIndex) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_VISUALINDEX, logicalIndex, 0);
        }
        
        public int logicalIndex(int visualIndex) {
            return QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_LOGICALINDEX, visualIndex, 0);
        }

        public void setSectionsMovable(bool movable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QH_SETSECTIONSMOVABLE, movable);
        }
        
        public bool sectionsMovable() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QH_SECTIONSMOVABLE);
        }

        public void setMovable(bool movable) { setSectionsMovable(movable); }
        
        public bool isMovable()  { return sectionsMovable(); }

        public void setSectionsClickable(bool clickable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QH_SETSECTIONSCLICKABLE, clickable);
        }
        
        public bool sectionsClickable() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QH_SECTIONSCLICKABLE);
        }

        public void setClickable(bool clickable) { setSectionsClickable(clickable); }
        
        public bool isClickable()  { return sectionsClickable(); }

        public void setHighlightSections(bool highlight){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QH_SETHIGHLIGHTSECTIONS, highlight);
        }
        
        public bool highlightSections() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QH_HIGHLIGHTSECTIONS);
        }

        public ResizeMode sectionResizeMode(int logicalIndex) {
            return (ResizeMode)QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_SECTIONRESIZEMODE, logicalIndex, 0);
        }
        
        public void setSectionResizeMode(ResizeMode mode){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QH_SETSECTIONRESIZEMODE, mode);
        }
        
        public void setSectionResizeMode(int logicalIndex, ResizeMode mode){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_SETSECTIONRESIZEMODE, logicalIndex, mode);
        }
        
        public void setResizeContentsPrecision(int precision){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QH_SETRESIZECONTENTSPRECISION, precision);
        }
        
        public int  resizeContentsPrecision() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_RESIZECONTENTSPRECISION);
        }

        public void setResizeMode(ResizeMode mode)
            { setSectionResizeMode(mode); }
            
        public void setResizeMode(int logicalindex, ResizeMode mode)
            { setSectionResizeMode(logicalindex, mode); }
            
        public ResizeMode resizeMode(int logicalindex) 
            { return sectionResizeMode(logicalindex); }

        public int stretchSectionCount() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_STRETCHSECTIONCOUNT);
        }

        public void setSortIndicatorShown(bool show){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QH_SETSORTINDICATORSHOWN, show);
        }
        
        public bool isSortIndicatorShown() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QH_ISSORTINDICATORSHOWN);
        }

        public void setSortIndicator(int logicalIndex, Qt.SortOrder order){
            QtXnl.widget_set_v2int_value(nativehandle, Constant.QH_SETSORTINDICATOR, logicalIndex, order);
        }
        
        public int sortIndicatorSection() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_SORTINDICATORSECTION);
        }
        
        public Qt.SortOrder sortIndicatorOrder() {
            return (Qt.SortOrder)QtXnl.widget_get_int_value(nativehandle, Constant.QH_SORTINDICATORORDER);
        }

        public bool stretchLastSection() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QH_STRETCHLASTSECTION);
        }
        
        public void setStretchLastSection(bool stretch){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QH_SETSTRETCHLASTSECTION, stretch);
        }

        public bool cascadingSectionResizes() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QH_CASCADINGSECTIONRESIZES);
        }
        
        public void setCascadingSectionResizes(bool enable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QH_SETCASCADINGSECTIONRESIZES, enable);
        }

        public int defaultSectionSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_DEFAULTSECTIONSIZE);
        }
        
        public void setDefaultSectionSize(int size){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QH_SETDEFAULTSECTIONSIZE, size);
        }
        
        public void resetDefaultSectionSize(){
            QtXnl.widget_slot(nativehandle,  Constant.QH_RESETDEFAULTSECTIONSIZE);
        }

        public int minimumSectionSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_MINIMUMSECTIONSIZE);
        }
        
        public void setMinimumSectionSize(int size){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QH_SETMINIMUMSECTIONSIZE, size);
        }
        
        public int maximumSectionSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_MAXIMUMSECTIONSIZE);
        }
        
        public void setMaximumSectionSize(int size){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QH_SETMAXIMUMSECTIONSIZE, size);
        }

        public int defaultAlignment() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QH_DEFAULTALIGNMENT);
        }
        
        public void setDefaultAlignment(int alignment){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QH_SETDEFAULTALIGNMENT, alignment);
        }

        public void doItemsLayout() {
            QtXnl.widget_slot(nativehandle,  Constant.QH_DOITEMSLAYOUT);
        }
        
        public bool sectionsMoved() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QH_SECTIONSMOVED);
        }
        
        public bool sectionsHidden() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QH_SECTIONSHIDDEN);
        }

        public byte[] saveState() {
            return (byte[])QtXnl.widget_get_object(nativehandle, Constant.QH_SAVESTATE);
        }
        
        public bool restoreState(byte[] state){
            QtXnl.widget_set_object_value(nativehandle, Constant.QH_LOADSTATE, state);
            return true;
        }
 
        public void reset() {
            QtXnl.widget_slot(nativehandle,  Constant.QH_RESET);
        }
        
        
        private onHeaderEventListener _listener = nilptr;
        
        public void setOnHeaderEventListener(onHeaderEventListener _l){
            _listener = _l;
        }
        
        public onHeaderEventListener getOnHeaderEventListener(){
            return _listener;
        }
        
        public void sectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex){
            if (_listener != nilptr){
                _listener.sectionMoved(this, logicalIndex, oldVisualIndex, newVisualIndex);
            }
        }
        public void sectionResized(int logicalIndex, int oldSize, int newSize){
            if (_listener != nilptr){
                _listener.sectionResized(this, logicalIndex, oldSize, newSize);
            }
        }
        public void sectionPressed(int logicalIndex){
            if (_listener != nilptr){
                _listener.sectionPressed(this, logicalIndex);
            }
        }
        public void sectionClicked(int logicalIndex){
            if (_listener != nilptr){
                _listener.sectionClicked(this, logicalIndex);
            }
        }
        public void sectionEntered(int logicalIndex){
            if (_listener != nilptr){
                _listener.sectionEntered(this, logicalIndex);
            }
        }
        public void sectionDoubleClicked(int logicalIndex){
            if (_listener != nilptr){
                _listener.sectionDoubleClicked(this, logicalIndex);
            }
        }
        public void sectionCountChanged(int oldCount, int newCount){
            if (_listener != nilptr){
                _listener.sectionCountChanged(this, oldCount, newCount);
            }
        }
        public void sectionHandleDoubleClicked(int logicalIndex){
            if (_listener != nilptr){
                _listener.sectionHandleDoubleClicked(this, logicalIndex);
            }
        }
        public void geometriesChanged(){
            if (_listener != nilptr){
                _listener.geometriesChanged(this);
            }
        }
        public void sortIndicatorChanged(int logicalIndex, int order){
            if (_listener != nilptr){
                _listener.sortIndicatorChanged(this, logicalIndex, (Qt.SortOrder)order);
            }
        }
    };
};