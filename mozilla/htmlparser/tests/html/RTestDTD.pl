#/usr/bin/perldie "\nUsage: perl RtestDTD.pl [FLAG] url_list.txt.FLAGS:  -v    = verify   ( would create rtest_html.veri )  -b    = baseline ( would create rtest_html.base )  -help = info. on running the script\n" if( @ARGV[0]!~/-help/ && ((@ARGV >2 || @ARGV < 2) || ($ARGV[0]!~m/-v/ && $ARGV[0]!~m/-b/)));if($ARGV[0]=~m/-help/) { print  "         1. \"url_list.txt\" can be generated by running UrlGen.pl            Ex. perl UrlGen.pl.         2. Run base line (-b) before making changes in your tree.            This will generate rtest_html.base file [DO NOT CHANGE THIS].         3. Run verification (-v) after making changes in your tree.            This will generate rtest_html.veri file and will compare            rtest_html.base and rtest_html.veri.NOTE:  Need perl version 5.0 or greater. \n"; exit(0);}use Cwd;$ENV{"PARSER_DUMP_CONTENT"}=1;($drive,@path)=split(/:/,`cd`);system("$drive:\\mozilla\\dist\\win32_d.obj\\bin\\viewer.exe -f $ARGV[1]");if($ARGV[0]=~m/-b/) {  rename("rtest_html.txt","rtest_html.base");}elsif($ARGV[0]=~m/-v/) {  rename("rtest_html.txt","rtest_html.veri");  @result=CompareFiles("rtest_html.base","rtest_html.veri");  Display(@result);}sub CompareFiles {  open(BASE,"<$_[0]") || die "Can't output $_[0] $!";  open(VERI,"<$_[1]") || die "Can't output $_[1] $!";  #Separate file contents into URL and DOCUMENT  while(<BASE>) {   ($url,$document1)=split/;/;   push(@url1,$url);   push(@documents1,$document1);  }  while(<VERI>) {   ($url,$document2)=split/;/;   push(@url2,$url);   push(@documents2,$document2);  }  #Search for documents that don't match  for($i=0;$i<=$#documents1+1;$i++) {   if($documents1[$i] !~ /$documents2[$i]/) {    (@string1)=split(//,$documents1[$i]);    (@string2)=split(//,$documents2[$i]);    for($j=0;$j<=$#string1;$j++) {     # Find the character that failed     if($string1[$j] !~ /$string2[$j]/) {       push(@result,$url1[$i],$string2[$j],$j);       $j=@string1; # Stop looping     }    }   }  }  close(BASE);  close(VERI);  return @result;}sub Display {  for($i=0;$i<@_;$i++) {   print "\n $_[$i++] failed on character '$_[$i++]' at location $_[$i]";  }  print "\n--------------------\n";  $count=@_/3;  if(($count)>0) {    print "$count url(s) failed\n";  }  else {    print "\nALL SUCCEEDED\n";  }}