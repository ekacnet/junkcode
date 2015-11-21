#!/usr/bin/perl

use strict;
use MIME::Parser;
my $msg = "";
my $in_header = 1;
my $in_spam_status = 0;
my $flag_spam = 0;
my $mail4spamc;
my $now = time();
my $dir = "/home/spamu/".int($now / 86400);
mkdir $dir if( ! -d "$dir" );

my $log_base = "$dir/${now}".int(rand(10000));
my $log = "${log_base}.status";
my $email = "${log_base}.eml";
my $spam = "${log_base}.spam";
my $log_handle;
my $email_handle;
my $spam_handle;
my $quiet = 0;
my $spamfilter="spamfilter.eurocopter.ru";
$quiet = 1 if( $ARGV[0] && $ARGV[0] eq "-q");
shift @ARGV if( $quiet );
#open (LOGG,">>$dir/argz");
#print LOGG join(" ",@ARGV)."\n\n";
#close(LOGG);
my $nothing = 0;
use YAML; 
my $skiplist = YAML::LoadFile("/usr/local/etc/catch_skiplist") if( -f "/usr/local/etc/catch_skiplist" );
while(<STDIN>)
{
  $in_header = 0 if( $in_header && m/^$/ );
  foreach my $skip (@$skiplist)
  {
    out(0) if( $in_header && m/$skip/ );
  }

  # if email is bayes_99 (99% or more of spamosity ...) discard ...
  $in_spam_status = 0 if( $in_spam_status && ( !$in_header || ( $in_header && m/^[^\s]/) ) );
  $in_spam_status = 1 if( $in_header && m/^X-Spam-Status:/ );
  out(0) if( $in_spam_status && m/BAYES_99/ );

  $flag_spam = 1 if( $in_header && m/^X-Spam-Flag: YES/ );
  
  #out(0) if( $in_header && m/^List-Id: .*.alerts.google.com/ );

  $msg.= $_;
}

log_msg("Got an email that worth learning spam on it\n") if(!$nothing);
log_msg("Doing nothing ...\n") if($nothing);

if( !$flag_spam )
{
  # easy way send all the message to spamc !!! 
  $mail4spamc = $msg;
}
else
{
  my $parser = new MIME::Parser;
  $parser->output_to_core(1);
  $parser->extract_nested_messages(0);
  my $entity=$parser->parse_data($msg);
  if( defined $entity->bodyhandle )
  {
    log_msg("Unexpected structure ... was waiting for a multipart email ....\n");
    out(0);
  }
  foreach my $nparts (0..$entity->parts)
  {
    my $type = $entity->parts($nparts)->head->get("Content-Type") if defined $entity->parts($nparts)->head;
    if( $type =~ m@^message/rfc822; x-spam-type=original@ )
    { 
      $mail4spamc = $entity->parts($nparts)->bodyhandle->as_string;
      last;
    }
  }
}
if( !$quiet)
{
  open($spam_handle,">$spam") || die "Unable to create spam file : $spam";
  print $spam_handle $mail4spamc ;
  close($spam_handle);
}

my $shandle;
open($shandle,"| /usr/bin/spamc -d $spamfilter -u spamu -L spam -s 750000");
if(defined $shandle)
{
  print $shandle $mail4spamc if( !$nothing );
  close($shandle);
}
else
{
  log_msg("Unable to feed spamc ...\n");
  out(1);
}

if( !$quiet )
{
  open($email_handle,">$email");
  if( !defined $email_handle )
  {
    log_msg("Can't write original email ...\n");
    out(1);
  }
  print $email_handle $msg if !$quiet;
}

out(0);

sub out
{
  my $code = shift;
  $code||= 0;
  close $log_handle if defined $log_handle;
  close $email_handle if defined $email_handle;
  exit $code;
}
sub log_msg
{
  return if $quiet;
  if( !defined $log_handle ) 
  {
    open($log_handle,">>$log") || die "Unable to create log file : $log";
  }
  print $log_handle shift;
}
