#!/bin/sh

#echo "Content-type: text/plain"
#echo ""

echo -n "Content-type: text/html
Cache-Control: no-cache

"

echo -n "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">
<html xmlns=\"http://www.w3.org/1999/xhtml\">
<head>
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">
<META HTTP-EQUIV=\"Pragma\" CONTENT=\"no-cache\">
<META HTTP-EQUIV=\"Cache-Control\" content=\"no-cache\">

</head>
<body>
";

if ($?WWW_name) then
    echo "Hi $WWW_name -- Nice to meet you."
else
    echo "Don't want to tell me your name, huh?"
    echo "I know you are calling in from $REMOTE_HOST."
    echo ""
fi

if ($?WWW_age) then
    echo "You are $WWW_age years old."
else
    echo "Are you shy about your age?"
fi
echo ""

if ($?WWW_drink) then
    echo "You like:" `echo $WWW_drink | tr "#" " "`
else
    echo "I guess you don't like any fluids."
fi

echo "<br><hr>"
date
echo "<br><hr>"

printenv

echo "<br><h2>"

uname -a

echo "</h2><hr>"

echo "</body>
</html>
";
exit 0
