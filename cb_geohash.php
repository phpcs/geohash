<?php
//测试

$arr = cb_geohash_decode("wt3nr0wvju7d");
$str = cb_geohash_encode(114.223446, 30.633511, 10);
var_dump($str);
var_dump($arr);
