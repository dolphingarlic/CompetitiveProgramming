# For each possible minimum value (except 15), 
# look for a cell that holds that many pebbles.
# Various optimizations reduce the number of instructions.

# The first step is looking for zeroes.
print "jump 0_scan_all"

for i in xrange(0,15):

  # This section tries to move on the next row after a single scan. If it hits
  # the border, we're ready to search for the next candidate minimum.
  print "%d_test_next_row:" % i
  print "right"
  print "border %d_scan_all" % (i+1)
  print "move"
  print "right"
  print "%d_test_next_row_l1:" % i
  print "border %d_test_next_row_l1end" % i
  print "move"
  print "jump %d_test_next_row_l1" % i
  print "%d_test_next_row_l1end:" % i
  print "right"

  # Start the evaluation of the next row of the grid.
  print "%d_scan_all:" % i
  print "right"
  print "%d_test_scan_row:" % i
  for j in xrange(i):
    print "get"
  print "pebble %d_test_scan_row_continue" % i
  print "jump end_%d" % i
  print "%d_test_scan_row_continue:" % i
  for j in xrange(i):
    print "put"
  # When it hits the border, try to go to the next row and go back to the
  # first column.
  print "border %d_test_next_row" % i
  print "move"
  print "jump %d_test_scan_row" %i

# When you find the minimum, you can share the code that puts back the pebbles
# in the cell.
for i in xrange(14,0,-1):
    print "end_%d:" % i
    print "put"
print "end_0:"
# If all the cells have 15 pebbles, any position is ok.
print "15_scan_all:"