# Install server engine

1.  First install unix odbc
    ```shell
      wget -c ftp://ftp.unixodbc.org/pub/unixODBC/unixODBC-2.3.1.tar.gz

      tar -xzvf unixODBC-2.3.1.tar.gz
      cd unixODBC-2.3.1;./configure --prefix=/usr/local/unixODBC --sysconfdir=/etc; make; make install
      cp /usr/local/unixODBC/lib/libodbc* /lib/ # if your system is 64bit then copy to /lib64/
    ```
2.  Install mysql odbc Driver
    ```shell
      wget -c http://cdn.mysql.com/Downloads/Connector-ODBC/5.2/mysql-connector-odbc-5.2.5-ansi-linux-glibc2.5-x86-32bit.tar.gz
      # if your system is 64bit then: 
      # wget -c http://cdn.mysql.com/Downloads/Connector-ODBC/5.2/mysql-connector-odbc-5.2.5-ansi-linux-glibc2.5-x86-64bit.tar.gz
      tar -xzvf mysql-connector-odbc-5.2.5-ansi-linux-glibc2.5-x86-32bit.tar.gz
      cd mysql-connector-odbc-5.2.5-ansi-linux-glibc2.5-x86-32bit
      mkdir -p /usr/local/mysql-connector-odbc; cp cp lib/libmyodbc5a.so /usr/local/mysql-connector-odbc
      cp /usr/local/unixODBC/lib/libodbcinst.so.2 /lib/libodbcinst.so.1 # or /lib64/libodbcinst.so.1
      cp /usr/local/unixODBC/lib/libodbc.so.2 /lib/libodbc.so.1 # or /lib64/libodbc.so.1
    ```
    
