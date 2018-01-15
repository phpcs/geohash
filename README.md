## 运行环境：
>geohash模块, 要求php>5, 暂不支持windows平台

## 安装此扩展步骤：
1. git clone
2. phpize
3. ./configure --with-php-config=/usr/bin/php-config　  此path换成你环境实际路径
4. sudo make && sudo make install
----------------------------------------

## 方法：
1. cb_geohash_decode()
2. cb_geohash_encode()


## 例：
```
$arr = cb_geohash_decode('wt3nr0wvju7d');
$str = cb_geohash_encode(114.223446, 30.633511, "12");

var_dump($arr);
var_dump($str);
```
-----------------------------------------------------
输出：

```
array(2) {
  ["lon"]=>
  float(114.22338869423)
  ["lat"]=>
  float(30.633511003107)
}
string(12) "wt3nr0wvju7d"


```
