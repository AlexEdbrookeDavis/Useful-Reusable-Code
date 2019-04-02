/* Unique.java
 */
 
public class Main
{
	
	public static void main(String[] args) {
		Duck mallard = new MallardDuck();
		Duck model = new ModelDuck();
		mallard.performQuack();
		mallard.performFly();
		model.performQuack();
		model.performFly();	
		model.setFlyBehavior(new RocketFlight());
		model.performFly();	
		}
}