//xlang Source, Name:DockToolBar.x 
//Date: Mon Feb 19:24:29 2021 

package Qtitan{
    public class DockToolBar : Qt.QWidget{
        public DockToolBar(){
            
        }
        
        public DockToolBar(long handle){
            super(handle);
        }

        public bool create(@NotNilptr Qt.QWidget parent)override {
            nativehandle = Qt.QtXnl.createQObject(Qt.QType.qtDockToolBar, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
       
        public bool create(@NotNilptr String titleText, @NotNilptr DockPanelManager parent) {
            nativehandle = Qt.QtXnl.createQSObject(Qt.QType.qtDockToolBar, this, parent.nativehandle, titleText);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }      
    };
};