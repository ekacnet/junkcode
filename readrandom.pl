
sub getKernelKey {
	my ($type) = @_;
	my @dbg = split('',"NeoterisDebugBld");
	use Data::Dumper;
	my $ret = "";
	open(RAND, "/dev/urandom");
	my $i = 0;
	my $i = 0;
	my @arr;
	while ($i < 16) {
		my $val;
		if ($type ne "production") {
			$val = $dbg[$i];
		} else {
			read(RAND, $val, 1);
		}
		push @arr, "0x".unpack("H2", $val);
		$i = $i + 1;
	}
	$ret = join(",",@arr);
	close(RAND);
	return $ret;
}

print getKernelKey("pouet")."\n";
print getKernelKey("production")."\n";
