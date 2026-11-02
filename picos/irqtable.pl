#!/usr/bin/perl

print "#include \"picos/config.h\"\n";
print "#include \"picos/asm.h\"\n";

print "begin_func  ___spurious_event, hot, global\n";
print "\tret\n";
print "end ___spurious_event\n";
print "\n";

print "begin_sdata ___irq_trap_table, 4, hot\n";

for (my $i = 31; $i > 0; $i--) {
    print "#if NR_IRQS >= $i\n";
    print "\t.word\t\t__irq_$i\n";
    print "\t.weakref\t__irq_$i, ___spurious_event\n";
    print "#endif\n\n";
}

print "\t.globl trap_table\n";
print "trap_table:\n";

for (my $i = 0; $i < 32; $i++) {
    print "\t.word\t\t__trap_$i\n";
    print "\t.weakref\t__trap_$i, ___spurious_event\n";
}

for (my $i = 0; $i < 32; $i++) {
    print "\t.word\t__ctrap_$i\n";
    print "\t.weakref\t__ctrap_$i, ___spurious_event\n";
}

print "end ___irq_trap_table\n";
