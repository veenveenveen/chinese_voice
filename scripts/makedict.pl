#!/usr/bin/perl
#
# make a used dict to solve the error 
# "ERROR [+8231]  GetHCIModel: Cannot find hmm ..." 
#
# Tonghua Su (in Chinese: ËÕÍ³»ª) 10.29.2006
#####################################################

if (@ARGV != 3) {
  print "usage: perl makedict.pl dict used_dict used_triphones\n\n"; 
  exit (0);
}

($dict, $used_dict, $used_triphones) = @ARGV;

# open dict and used_triphones to read
open(DICT, "$dict");
open(TRIPHONES, "$used_triphones");

# open used_dict to write
open(USEDDICT, ">$used_dict");

#
%triHash=(); 
while ($triphone = <TRIPHONES>) {
	chop($triphone);
	$triHash{"$triphone"}=1;
}
	
while (<DICT>) {
	chop($_);
	@phones=split;
	$num2=@phones[2];
	#print $num2;
	if (@phones<4){
		if ($num2 eq "sil") {
			print USEDDICT "$_\n";
			next;
		}
		else{
			if (not (exists($triHash{"$num2"}))){
				goto InsComm
			}
		}
	}
	else{
		
		for ($numPhone=2;$numPhone<@phones-2;$numPhone++)
		{
			$bef=@phones[$numPhone-1];
			$cur=@phones[$numPhone];
			$aft=@phones[$numPhone+1];
			#print "$bef-$cur+$aft\n";
			if (not (exists($triHash{"$bef-$cur+$aft"}))){
			goto InsComm
			#print USEDDICT "#$_\n";
			}
		}
		$cur=@phones[1];
		$aft=@phones[2];
		#print "$cur+$aft\n";
		if (not exists($triHash{"$cur+$aft"})){
			goto InsComm
			#print USEDDICT "#$_\n";
		}
		
		$bef=@phones[@phones-3];
		$cur=@phones[@phones-2];
		#print "$bef-$cur\n";
		if (not exists($triHash{"$bef-$cur"})){
			goto InsComm
			#print USEDDICT "#$_\n";
		}
	}
	print USEDDICT "$_\n";
	next;
	InsComm:
	print USEDDICT "#$_\n";
	print "$_ IS marked as a COMMENT.\n"
}
close DICT;
close TRIPHONES;
close USEDDICT;
