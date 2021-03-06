<!--
 Example PVWatts V5 calculator web application using SSC PHP extension
  Written by Aron Dobos @ NREL 
-->
<?php 

$wfdir = "./weather";

$loc = $_GET["location"];
$size = $_GET["size"];
$dcacratio = $_GET["dcacratio"];
$inveff = $_GET["inveff"];
$module = $_GET["module"];
$array = $_GET["array"];
$losses = $_GET["losses"];
$tilt = $_GET["tilt"];
$azimuth = $_GET["azimuth"];
$gcr = $_GET["gcr"];

$loc = str_replace(".", "", $loc );
$loc = str_replace("/", "", $loc );

?>

<!doctype html>
<html>
<head>
<title>PVWatts Calculator Demo</title>

	<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.8.3/jquery.min.js"></script>
	<script type="text/javascript" src="jquery.searchabledropdown-1.0.8.min.js"></script>
	
	<script type="text/javascript">
		$(document).ready(function() {
			$("#location").searchable({
	        maxListSize: 100,                       // if list size are less than maxListSize, show them all
	        maxMultiMatch: 50,                      // how many matching entries should be displayed
	        exactMatch: false,                      // Exact matching on search
	        wildcards: true,                        // Support for wildcard characters (*, ?)
	        ignoreCase: true,                       // Ignore case sensitivity
	        latency: 30,                           // how many millis to wait until starting search
	        warnMultiMatch: 'top {0} matches ...',  // string to append to a list of entries cut short by maxMultiMatch
	        warnNoMatch: 'no matches ...',          // string to show in the list when no entries match
	        zIndex: 'auto'                          // zIndex for elements generated by this plugin
	    });
		});
		
	</script>

<style>
table, th, td {
	border-collapse: collapse;
	font: 13px Georgia;
	padding: 3px;
	border: 1px dotted #888;
	text-align: center;
	color: #888;
	background-color:white;
}
th {
	font: 14px Georgia;
}

.basic-grey {
    margin-left:auto;
    margin-right:auto;
    max-width: 575px;
    background: #F7F7F7;
    padding: 25px 15px 25px 10px;
    font: 12px Georgia, "Times New Roman", Times, serif;
    color: #888;
    text-shadow: 1px 1px 1px #FFF;
    border:1px solid #E4E4E4;
}
.basic-grey h1 {
    font-size: 29px;
    padding: 0px 0px 10px 40px;
    display: block;
    border-bottom:1px solid #E4E4E4;
    margin: -10px -15px 30px -10px;;
    color: #888;
}
.basic-grey h1>span {
    display: block;
    font-size: 11px;
}
.basic-grey h3 {
    font-size: 20px;
    padding: 0px 0px 10px 40px;
    display: block;
    border-bottom:1px solid #E4E4E4;
    margin: -10px -15px 30px -10px;;
    color: #888;
}

.basic-grey h3>span {
    display: block;
    font-size: 11px;
}
.basic-grey label {
    display: block;
    margin: 0px;
}
.basic-grey label>span {
    float: left;
    width: 25%;
    text-align: right;
    padding-right: 10px;
    margin-top: 8px;
    color: #888;
}
.basic-grey input[type="text"], .basic-grey input[type="email"], .basic-grey textarea {
    border: 1px solid #DADADA;
    color: #888;
    height: 20px;
    margin-bottom: 5px;
    margin-right: 6px;
    outline: 0 none;
    padding: 3px 3px 3px 5px;
    width: 65%;
    font-size: 12px;
    line-height:15px;
    box-shadow: inset 0px 1px 4px #ECECEC;
    -moz-box-shadow: inset 0px 1px 4px #ECECEC;
    -webkit-box-shadow: inset 0px 1px 4px #ECECEC;
}
.basic-grey textarea{
    padding: 5px 3px 3px 5px;
}
.basic-grey select {
    border: 1px solid #DADADA;
    color: #888;
    margin-bottom: 5px;
    margin-right: 6px;
    margin-top: 2px;
	line-height: 25px;
    outline: 0 none;
    padding: 3px 3px 3px 5px;
    font-size: 12px;
    box-shadow: inset 0px 1px 4px #ECECEC;
    -moz-box-shadow: inset 0px 1px 4px #ECECEC;
    -webkit-box-shadow: inset 0px 1px 4px #ECECEC;
	
    background: #FFF url('down-arrow.png') no-repeat right;
    appearance:none;
    -webkit-appearance:none;
    -moz-appearance: none;
    text-indent: 0.01px;
    text-overflow: '';
    width: 40%;
}
.basic-grey textarea{
    height:100px;
}
.basic-grey .button {
    background: #E27575;
    border: none;
    padding: 10px 25px 10px 25px;
    color: #FFF;
    box-shadow: 1px 1px 5px #B6B6B6;
    text-shadow: 1px 1px 1px #9E3F3F;
    cursor: pointer;
}
.basic-grey .button:hover {
    background: #CF7A7A
}
</style>

</head>

<form action="pvwatts.php" method="GET" class="basic-grey">
<h1>PVWatts Version 5 Calculator Demo
	<span>
	<?php
		echo "Using SSC Version " .		sscphp_version() . ", compiled on " . sscphp_build_info();
	?>
	</span>
</h1>


<h3> Enter a city or country name:
<span>
<select name="location" id="location" style="width:90%; font-size:16px">
	<?php
	$weather = scandir( "./weather" );
	foreach( $weather as $file )
	{
		if ( $file == "." || $file == ".." ) continue;
		$name = pathinfo( $wfdir . "/" . $file, PATHINFO_FILENAME);
		$sel = "";
		if($loc == $name){$sel=" selected";} 
		echo "<option value=\"$name\" $sel>$name</option>\n";
	}
	?>
</select></span></h3>


<label>
	<span> System size (kW): </span>
	<input id="size" type="text" name="size" value="<?php echo $size != null && $size >= 1 ? $size : "4.0";?>" onClick="this.select();">
</label>

<label>
	<span> DC to AC ratio : </span>
	<input id="dcacratio" type="text" name="dcacratio" value="<?php echo $dcacratio != null && $dcacratio < 5 && $dcacratio > 0.5 ? $dcacratio : "1.1";?>" onClick="this.select();">
</label>


<label>
	<span> Inverter efficiency (%): </span>
	<input id="inveff" type="text" name="inveff" value="<?php echo $inveff != null && $inveff <= 99.5 && $inveff > 10 ? $inveff : "96.0";?>" onClick="this.select();">
</label>

<label>
	<span> Module type: </span>
	<select name="module" value="<?php echo $module;?>">
		<option <?php if($module == '0'){echo("selected");}?> value="0">Standard</option>
		<option <?php if($module == '1'){echo("selected");}?> value="1">Premium</option>
		<option <?php if($module == '2'){echo("selected");}?> value="2">Thin film</option>
	</select>
</label>
	
<label>
	<span> Array type: </span>
	<select name="array" value="<?php echo $array;?>">
		<option <?php if($array == '0'){echo("selected");}?> value="0">Fixed (open rack)</option>
		<option <?php if($array == '1'){echo("selected");}?> value="1">Fixed (roof mount)</option>
		<option <?php if($array == '2'){echo("selected");}?> value="2">1-Axis tracking</option>
		<option <?php if($array == '3'){echo("selected");}?> value="3">1-Axis backtracking</option>
		<option <?php if($array == '4'){echo("selected");}?> value="4">2-Axis tracking</option>
	</select>
</label>

<label>
	<span> Losses (%): </span>
	<input id="losses" type="text" name="losses" value="<?php echo $losses != null && $losses < 70 && $losses > -5 ? $losses : "14.0";?>" onClick="this.select();">
</label>

<label>
	<span> Tilt (deg): </span>
	<input id="tilt" type="text" name="tilt" value="<?php echo $tilt != null && $tilt >= 0 && $tilt <= 90 ? $tilt : "20.0";?>" onClick="this.select();">
</label>

<label>
	<span> Azimuth (deg): </span>
	<input id="azimuth" type="text" name="azimuth" value="<?php echo $azimuth != null && $azimuth >= 0 && $azimuth < 359.9 ? $azimuth : "180.0";?>" onClick="this.select();">
</label>


<label>
	<span> GCR (1 axis only) : </span>
	<input id="gcr" type="text" name="gcr" value="<?php echo $gcr != null && $gcr > 0 && $gcr < 1.0 ? $gcr : "0.4";?>" onClick="this.select();">
</label>


<label>
	<span> &nbsp; </span>
	<input type="button" class="button" onclick="this.form.submit()" value="Calculate" /> 
</label>

</form>


<?php

$wf = realpath( $wfdir . "/" . $loc . ".csv");
$ok = false;
if ( file_exists($wf) )
{
	$dat = sscphp_data_create();
	
	sscphp_data_set_string( $dat, "solar_resource_file", $wf );
	sscphp_data_set_number( $dat, "system_capacity", $size );
	sscphp_data_set_number( $dat, "module_type", $module );
	sscphp_data_set_number( $dat, "dc_ac_ratio", $dcacratio );
	sscphp_data_set_number( $dat, "inv_eff", $inveff );
	sscphp_data_set_number( $dat, "losses", $losses );
	sscphp_data_set_number( $dat, "array_type", $array );
	sscphp_data_set_number( $dat, "tilt", $tilt );
	sscphp_data_set_number( $dat, "azimuth", $azimuth );
	sscphp_data_set_number( $dat, "gcr", $gcr );
	sscphp_data_set_number( $dat, "adjust:constant", 0 );
	
	$mod = sscphp_module_create( "pvwattsv5" );
	if ( sscphp_module_exec( $mod, $dat ) )
	{
		$annual = sscphp_data_get_number( $dat, "annual_energy" );
		$monthly = sscphp_data_get_array( $dat, "monthly_energy" );
		$solrad = sscphp_data_get_array( $dat, "solrad_monthly" );
		$latitude = sscphp_data_get_number( $dat, "lat" );
		$longitude = sscphp_data_get_number( $dat, "lon" );
		$ok = true;
	}
	else
	{
		$index = 0;
		while ($err = sscphp_module_log( $mod, $index++ ) )
		{
			echo "$err<br>\n";
		}
	}
	
	sscphp_module_free( $mod );
	sscphp_data_free( $dat );
}


if ( $ok )
{
	$months = array( "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" );
?>

<div class="basic-grey">
<h1><?php echo round($annual); ?> kWh per year
<span> <?php echo $loc . "&nbsp;&nbsp;&nbsp;coordinates: " . round($latitude,4) . ",&nbsp;&nbsp;" . round($longitude,4) ;?> </span>
	</h1>

<label>
	<table>
<tr><th>Month<br>&nbsp;</th><th>Energy<br>(kWh)</th><th>Radiation<br>(kWh/m<sup>2</sup>/day)</th></tr>

<?php
for( $i=0;$i<12;$i++ )
{
	echo "<tr><td>$months[$i]</td>";
	echo "<td>" . round($monthly[$i]) . "</td>";
	echo "<td>" . round($solrad[$i],2) . "</td></tr>\n";
}

?>

</table>
</label>

<?php
}
?>
</div>

</body>
</html>
