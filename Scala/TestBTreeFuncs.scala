
//Binary tree code
sealed abstract class Tree[+T] {
	def isMirrorOf[V](tree: Tree[V]): Boolean
	def isSymmetric: Boolean
	def addValue[U >: T <% Ordered[U]](x: U): Tree[U]
	def leafCount: Int

}

case class Node[+T](value: T, left: Tree[T], right: Tree[T]) extends Tree[T] {
	override def toString = "T(" + value.toString + " " + left.toString + " " + right.toString + ")"
  
	def isMirrorOf[V](tree: Tree[V]): Boolean = tree match {
		case t: Node[V] => left.isMirrorOf(t.right) && right.isMirrorOf(t.left)
		case _          => false	
	}
	
	def isSymmetric: Boolean = left.isMirrorOf(right)
	
	def addValue[U >: T <% Ordered[U]](x: U): Tree[U] = {
		if(x < value) Node(value, left.addValue(x), right)
		else Node(value, left, right.addValue(x))
	}
	
	def leafCount: Int = (left, right) match {
		case (End, End) => 1
		case _			=> left.leafCount + right.leafCount
	}

}

case object End extends Tree[Nothing] {
	override def toString = "."
	def isMirrorOf[V](tree: Tree[V]): Boolean = tree == End
	def isSymmetric: Boolean = true
	def addValue[U <% Ordered[U]](x: U): Tree[U] = Node(x, End, End)
	def leafCount: Int = 0
}

object NodeE {
  def apply[T](value: T): Node[T] = Node(value, End, End)
}

object BTreefuncs {
	def cBalanced[A](num: Int, input: A): List[Tree[A]] = num match {
		case n if n < 1			=> List(End)
		case n if (n % 2) == 1		=> {
			val subtrees = cBalanced(n / 2, input)
			subtrees.flatMap(l => subtrees.map(r => Node(input, l, r)))			
		}
		case n if (n % 2) == 0 		=> {
			val lesserSubtrees = cBalanced((n - 1) / 2, input)
			val greaterSubtrees = cBalanced((n - 1) / 2 + 1, input)
			lesserSubtrees.flatMap(l => greaterSubtrees.flatMap(g => List(Node(input, l, g), Node(input, g, l))))
		}
	}

	
}

object TestBTreeFuncs {
	def main(args: Array[String]) {
		print(Node('a', Node('b', NodeE('d'), NodeE('e')), Node('c', End, Node('f', NodeE('g'), End))) + "\n")
		print(BTreefuncs.cBalanced(2, "x") + "\n")
		print((Node(1, End, End)).isSymmetric + "\n")
		print((Node(1, End, Node(3, End, End))).addValue(2) + "\n")
		//skip 58,59,60
		print((Node(1, End, Node(3, End, End))).leafCount + "\n")
	}
}