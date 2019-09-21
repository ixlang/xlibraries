##包 ： Sql

## 提供xlang的sqlite和mysql;sqlserver在 windows和linux下的数据库操作


## 说明

注意 sqlserver 仅支持 windows
提供xlang的sqlite和mysql在 windows和linux下的数据库操作

示例
Sql.Connection conn = Sql.Database.getConnection("sqlserver");
if (conn != nilptr){
	try{
    	conn.create("127.0.0.1", "sa", "123456");

    	Sql.PreparedStatement stmt = slite.prepareStatement("CREATE table blog..member(name varchar(32),age int)");

    	stmt.executeUpdate();

    	stmt = slite.prepareStatement("select top 10 * from blog..member where age < ?");
        
        stmt.setValue(40);

        注意:遍历结果用法不同.

        /// sqlserver 遍历 ResultSet
        Sql.ResultSet rs = stmt.executeQuery();
        int c = rs.getRowCount();
        while (rs.isEof() == false){
            _system_.consoleWrite(new String(rs.getString("name").getBytes("GB18030//IGNORE")) + ":" + rs.getString("age") + "\n");
            rs.next();
        }

        //mysql和sqlite 遍历 ResultSet
        Sql.ResultSet rs = stmt.executeQuery();
        int c = rs.getRowCount();
        while (rs.next()){
            //_system_.consoleWrite(new String(rs.getString("name").getBytes("GB18030//IGNORE")) + ":" + rs.getString("age") + "\n");
        }

        conn.close();
    }catch(Exception e){
    	_system_.consoleWrite("SqlException:" + e.getErrorCode() + "," + e.getMessage() + "\n");
    }catch(SqlException e1){
        _system_.consoleWrite("SqlException:" + e.getErrorCode() + "," + e.getMessage() + "\n");
    }
}
## github地址 https://github.com/ixlang/xlibrarys
