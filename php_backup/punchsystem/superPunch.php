<?php

    $account = $_GET['acc'];
    $Time = $_GET['time'];
    $Date = $_GET['date'];
    $status = $_GET['stat'];
    

    $host = "localhost";
    $username = "root";
    $userpass = "";
    $dbname = "punchsystem";

     $con = mysqli_connect($host, $username, $userpass, $dbname);

    if (!$con) {
        die("Connection failed!" . mysqli_connect_error());
    }

    $chk_acc = "SELECT * FROM `UserData` WHERE `account` = '$account';";
    $chk_acc_ret = mysqli_query($con,$chk_acc);
    if ($chk_acc_ret){
        if (!mysqli_num_rows($chk_acc_ret)) {
            
            echo "<script>";
            echo "alert('Fail to assign salary, Account: $account does not exist.');";
            echo "window.history.back();";
            echo "</script>";
        }
    }

    $sql = "INSERT INTO `punch-record`(`account`, `date`, `time`, `status`) VALUES ('$account','$Date','$Time','$status');";
    $ret = mysqli_query($con,$sql);

    // // $sql = "INSERT INTO punch-record (account,date,time,status) VALUES ('$account','$Date','$Time','$status');";

    if ($ret){
        echo "<script> alert('punch '+'$status'+' successful');window.location.href='superHome.php?account=admin&date=$Date&page=Rpage';</script>";
    }
    else {
        echo "<script> alert('punch '+'$status'+' fail');window.location.href='superHome.php?account=admin';</script>";
    }
    
    mysqli_close($con);

?>