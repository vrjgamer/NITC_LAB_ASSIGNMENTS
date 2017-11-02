<!DOCTYPE HTML>
<html>

<head>
    <title>DBMS Lab</title>
    <style>
        html,
        body {
            height: 100%;
            width: 100%;
            background: black;
            color: white;
        }
        
        header {
            min-height: 60px;
            line-height: 60px;
            font-size: 40px;
            text-align: center;
            background: brown;
            margin: 0px 10px 10px 10px;
        }
        
        input {
            height: 30px;
            line-height: 30px;
            display: block;
            padding-left: 10px;
            margin: 0px 0px 10px 20px;
        }
        
        input[type="radio"] {
            display: inline;
        }
        
        input[type="submit"] {
            margin-top: 30px;
            background: orange;
            border-radius: 10px;
            border: none;
            color: black;
        }
    </style>


</head>

<body>
    <header>COMPANY DATABASE</header>

    <div class="input_holder">
        <h2>Employee Details</h2>
        <form method="post" action="save.php">
            <input type="text" placeholder="First Name" name="employee_first_name" />
            <input type="text" placeholder="Middle Name" name="employee_middle_name" />
            <input type="text" placeholder="Last Name" name="employee_last_name" />
            <input type="radio" name="employee_sex" id="radio_male" value="Male" />
            <lable for="radio_male">Male</lable>
            <input type="radio" name="employee_sex" id="radio_female" value="Female" />
            <lable for="radio_female">Female</lable>
            <input type="text" name="employee_salary" placeholder="Salary" />
            <input type="text" name="employee_address" placeholder="Address" />
            <input type="date" name="employee_dob" placeholder="Date of Birth" />
            <input type="number" name="employee_ssn" placeholder="SSN" />
            <input type="submit" name="submit" />
        </form>
    </div>
</body>

</html>


<?php
	
?>