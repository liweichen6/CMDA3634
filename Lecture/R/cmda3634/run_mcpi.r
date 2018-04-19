#Script to calculate pi using Monte Carlo

#Load the function to calculate pi
source('mcpi.r')

#problem size (number of points)
n.pts <- 1e7

cat('running serial version with n.pts = ',n.pts,'\n')

tm.st = Sys.time()

pi.approx <- mcpi(n.pts)
cat('     pi estimate = ',pi.approx,'\n')

pi.err = abs(pi - pi.approx)/pi
cat('  relative error = ',pi.err,'\n')

tm.tot = as.numeric(Sys.time() - tm.st, units="secs")
cat('       time used = ',tm.tot,'\n')
