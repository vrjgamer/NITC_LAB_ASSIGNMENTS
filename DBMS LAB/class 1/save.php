<?php
	if($_SERVER["REQUEST_METHOD"] == "POST"){
			$fName = $_POST["employee_first_name"];
			$mName = $_POST["employee_middle_name"];
			$lName = $_POST["employee_last_name"];
			$sex = $_POST["employee_sex"];
			$salary = $_POST["employee_salary"];
			$address = $_POST["employee_address"];
			$DOB = $_POST["employee_dob"];
			$SSN = $_POST["employee_ssn"];
			
			if($fName != "" && $sex != "" && $DOB != null){
				$newEmployee = "\n{\n\tName: " .$fName." ". $mName ." ". $lName ."\n".
				"\tSex: ". $sex . "\n".
				"\tAddress: ". $address . "\n". 
				"\tDOB: ". $DOB ."\n"."\tSSN: ". $SSN . "\n}\n";
				
				$myfile = fopen("db.txt", "a");
				fwrite($myfile, $newEmployee);
				fclose($myfile);
			}
		}
?>
