//xlang Source, Name:qt5/titan/DockStyleConfig.x 
//Date: Tue Feb 21:52:49 2021 
package Qtitan{
    public class DockStyle : Qt.QStyle{
        public DockStyle(){
            
        }
        public DockStyle(long h){
            super(h);
        }
        public bool create(String path, Qt.QByteArray qb){
            nativehandle = Qt.QtXnl.createQSObject(Qt.QType.qtDockStyle, this, qb.nativehandle, path);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
                
        public Theme theme(){
            return (Theme)Qt.QtXnl.widget_get_int_value(nativehandle, Qt.Constant.QTNDS_THEME);
        }
        
        public void setTheme(Theme theme){
            Qt.QtXnl.widget_set_vint_value(nativehandle, Qt.Constant.QTNDS_SETTHEME, theme);
        }
    };
};