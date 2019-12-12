package hr.fer.aoc;

public class Moon {
	private Vector position;
	private Vector velocity;
	private Vector positionOriginal;
	private int changeX, changeY, changeZ;

	public Moon(Vector position) {
		this(position, new Vector());
	}

	public Moon(Vector position, Vector velocity) {
		super();
		this.position = position;
		this.velocity = velocity;
		changeX = changeY = changeZ = 0;

		this.positionOriginal = new Vector(position.getX(), position.getY(), position.getZ());
	}

	public void compareTo(Moon other) {
		if (this.position.getX() > other.getPosition().getX()) {
			updateChange('x', -1);
			other.updateChange('x', 1);

		} else if (this.position.getX() < other.getPosition().getX()) {
			updateChange('x', 1);
			other.updateChange('x', -1);
		}

		if (this.position.getY() > other.getPosition().getY()) {
			updateChange('y', -1);
			other.updateChange('y', 1);

		} else if (this.position.getY() < other.getPosition().getY()) {
			updateChange('y', 1);
			other.updateChange('y', -1);
		}

		if (this.position.getZ() > other.getPosition().getZ()) {
			updateChange('z', -1);
			other.updateChange('z', 1);

		} else if (this.position.getZ() < other.getPosition().getZ()) {
			updateChange('z', 1);
			other.updateChange('z', -1);
		}
	}

	public void applyGravity() {
		velocity.setX(velocity.getX() + changeX);
		velocity.setY(velocity.getY() + changeY);
		velocity.setZ(velocity.getZ() + changeZ);
	}

	public void applyVelocity() {
		position.setX(position.getX() + velocity.getX());
		position.setY(position.getY() + velocity.getY());
		position.setZ(position.getZ() + velocity.getZ());
		resetChange();
	}

	private void resetChange() {
		changeX = changeY = changeZ = 0;
	}

	public Vector getPosition() {
		return position;
	}

	public Vector getVelocity() {
		return velocity;
	}

	public int getPotEnergy() {
		return Math.abs(this.position.getX()) + Math.abs(this.position.getY()) + Math.abs(this.position.getZ());
	}

	public int getKinEnergy() {
		return Math.abs(this.velocity.getX()) + Math.abs(this.velocity.getY()) + Math.abs(this.velocity.getZ());
	}

	public int getEnergy() {
		return this.getPotEnergy() * this.getKinEnergy();
	}

	public void setChange(int a, int b, int c) {
		this.changeX = a;
		this.changeY = b;
		this.changeZ = c;
	}

	public void updateChange(char c, int i) {
		switch (c) {
		case 'x':
			changeX += i;
			break;
		case 'y':
			changeY += i;
			break;
		case 'z':
			changeZ += i;
			break;
		default:
			break;
		}
	}

	public boolean isStart() {
		return this.position.equals(positionOriginal);
	}

	@Override
	public String toString() {
		return "pos=" + position.toString() + ", vel=" + velocity.toString();
	}
}
