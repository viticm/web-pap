Install server engine
=====================

1.  First install unix odbc
    ```shell
      wget -c ftp://ftp.unixodbc.org/pub/unixODBC/unixODBC-2.3.1.tar.gz.

      use: ./configure --prefix=/usr/local/unixODBC --sysconfdir=/etc; make; make install.
    ```
2. Install mysql odbc Driver
    ```shell
      You can enter internet page: ```html http://dev.mysql.com/downloads/mirror.php?id=412796 ```

      Downown a mysql-connector-odbc, and get the lib to your system .

      You can copy it to a file, example: /usr/local/mysql-connector-odbc/libmyodbc5a.so .

      Then you need set /etc/odbc.ini param:  Driver = /usr/local/mysql-connector-odbc/libmyodbc5a.so .

      Because this lib based on odbc 1.0, so you can copy the new libodbc.so.2 and libodbcinst.so.2 
    convert to /lib64/libodbc.so.1 /lib64/libodbcinst.so.1,
    
      if your system bit is 32 then copy to /lib/libodbc.so.1 /lib/libodbcinst.so.1 .
    ```
