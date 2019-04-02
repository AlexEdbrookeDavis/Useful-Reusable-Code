/* ModelDuck.java
 */
 

public class ModelDuck extends Duck
{	
	public ModelDuck() {
		quackBehavior = new Quack();
		flyBehavior = new NoFly();
	}
	
	public void display() {
		System.out.println("This is a model duck.");
	}

}