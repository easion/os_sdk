#!/bin/sh
#This script is created by ssparser automatically. The parser first created by MaoShouyan
echo -n "Content-type: text/html
Cache-Control: no-cache

"
echo -n "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">
<html xmlns=\"http://www.w3.org/1999/xhtml\">
<head>
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">
<META HTTP-EQUIV=\"Pragma\" CONTENT=\"no-cache\">
<META HTTP-EQUIV=\"Cache-Control\" content=\"no-cache\">
<link rel=\"stylesheet\" type=\"text/css\" href=\"/image/dtree.css\" />
<script type=\"text/javascript\" src=\"/image/dtree.js\"></script>
<script type=\"text/javascript\">
function openurl(url)
{
        window.parent.document.all(\"content\").src = url;
}
</script>
</head>
<body>
<div style=\"position:absolute;top:6px\">
<script type=\"text/javascript\">
	d = new dTree('d');
	d.add(0, -1, '网络配置');
	d.add(10, 0, '管理接口', \"javascript:openurl('/cgi-bin/Setup/if_admin')\");
        d.add(11, 0, '数据接口', \"javascript:openurl('/cgi-bin/Setup/if_data')\");
	document.write(d);
</script>
</div>
</body>
</html>
";
