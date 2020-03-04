<!DOCTYPE html>
<?php
include 'connection.php';
?>

<head>
    <title>Project Lab 2 Log</title>
    <link rel="stylesheet" href="../add.css">
    <script src="../jquery.js"></script>
    <script>
    //jquery script to auto refresh the table
    //waits until data is available 
    $(document).ready(function() {
        setInterval(function() {
            $('#x').load('loadtable.php')
        }, 0.3); //delay in ms
    });
    </script>
    <style>
    section.two {
        align: floatval;
    }

    table {
        border-width: 3px black;
        text-align: center;
        display: inline-block;
        border-spacing: 0px;
    }

    section.Battery {
        float: left;
    }

  
    th,
    td {
        border: 1px solid black;
        padding: 5px;
        text-align: left;
    }

    tr:hover {
        background-color: orange;
    }

    section.one {
        text-align: center;
        float: left;
    }


    </style>
</head>


<body>
    <header>
        <nav>
            <div class="b"><a href="../start.html">Main</a></div>
            <div class="b"><a href="log.php">Log</a></div>
        </nav>
    </header>

    <section class="main">
        <em>
            <h2>Battery Monitoring System</h2>
            
        </em>
        <h2>Log Page</h2>
    </section>

    <section class="Battery">

        <table>
            <p>Battery Charge Monitoring</p>
            <thead>
                <th>Battery Charge</th>
                <th>UTC Time</th>
                
            </thead>
            <thead id="x"></thead>
        </table>
    </section>


</body>