# This function is invoked by the C program r_test

tauxOccupation <- function(a) {
  cat("R à reçu : ", a, "\n");

  b = (a[1] * 100) / a[2] 

  return (b)
}
