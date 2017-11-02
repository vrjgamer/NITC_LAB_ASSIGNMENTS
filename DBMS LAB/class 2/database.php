<?php
    
    $user = "";
    $password = "";
    $host = "";
    $connection = null;
    $database = null;
    function connect_to_mysql(){
        $connection = mysql_connect($user, $password, $host);
        if(!$connection){
            die('Could not connect: ' . mysql_error());
          }
        echo 'Connected successfully\n';
    }

    function disconnect_from_mysql(){
            if($connection != null)
                mysql_close($connection);
    }
    
    function createDatabase($database_name){
        $createDBSQL = "CREATE DATABASE " . $database_name;
        if($connection != null){
            $database = mysql_query($createSQL, $connection);
            if(!$database){
                die('Could not create database: ' . mysql_error());
            }
            echo "Database ".$database_name." created successfully\n";
        }
    }

    function loadDatabase($database_name){
         if($connection != null){
             $database = mysql_select_db($database_name, $connection);
            if(!$database){
                die('Could not load database: ' . mysql_error());
            }
            echo "Database ".$database_name." selected\n";
         } 
    }
   
    function createTable($table_details_sql){
        if($connection != null){
            $database = mysql_query($table_details_sql, $connection);
            if(!$database){
                die('Could not create Table: ' . mysql_error());
            }
            echo "Table created successfully\n";
        }
    }
   
    

    disconnect_from_mysql();
?>