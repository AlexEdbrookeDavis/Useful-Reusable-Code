object Mathfuncs {

	//The below uses a stream to reduce initial calculation cost
	def primeStream[A](s: Stream[Int]): Stream[Int] = {
		s.head #:: primeStream(s.tail filter { _ % s.head != 0 }) // This filters multiples of each prime
	}
	val primeStream: Stream[Int] = primeStream(Stream.from(2)) //from is all numbers starting with 2

	def isPrime(n: Int): Boolean = {
		def isPrimeRec(n: Int, primes: Stream[Int]): Boolean = primes match {
			case x #:: tail => {
				if (x == n) true
				else if (x > n) false
				else isPrimeRec(n, tail)
			}
		}
		isPrimeRec(n, primeStream)
	}
	
	def gcd(n: Int, m: Int): Int = (n, m) match {
		case (n, 0)		=> n
		case (n, m)		=> gcd(m, n % m)
	}
	
	def isCoprimeTo(n: Int, m: Int): Boolean = gcd(n, m) == 1
	
	def totient(n: Int): Int = (((1 to n)).filter({ isCoprimeTo(n, _) })).length
	
	def primeFactors(n: Int): List[Int] = {
		def primeFactorsRec(n: Int, primes: Stream[Int]): List[Int] = {
			if (isPrime(n)) List(n)
			else if (n % primes.head == 0) primes.head :: primeFactorsRec(n / primes.head, primes)
			else primeFactorsRec(n, primes.tail)
		}
		primeFactorsRec(n, primeStream)
	}
	
	def listPrimesinRange(r: Range): List[Int] =
		(primeStream dropWhile { _ < r.start } takeWhile { _ <= r.end }).toList
		
	def goldbach(n: Int): (Int, Int) = {
		primeStream takeWhile { _ < n } find { p => isPrime(n - p) } match {
			case None     => throw new IllegalArgumentException
			case Some(p1) => (p1, n - p1)
		}
	}
}

object TestMathFuncs {
	def main(args: Array[String]) {
		val list: List[Int] = List(1, 2, 3)
		print(Mathfuncs.primeStream + "\n")
		print(Mathfuncs.isPrime(13) + "\n")
		print(Mathfuncs.primeStream + "\n")
		print(Mathfuncs.gcd(36, 63) + "\n")
		print(Mathfuncs.isCoprimeTo(35, 64) + "\n")
		print(Mathfuncs.totient(10) + "\n")
		print(Mathfuncs.primeFactors(315) + "\n")
		//Skipping 36, 37, 38
		print(Mathfuncs.listPrimesinRange(7 to 31) + "\n")
		print(Mathfuncs.goldbach(28) + "\n")
		//skipping 41
	}
}