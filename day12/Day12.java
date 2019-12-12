package hr.fer.aoc;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;

public class Day12 {

	public static final int steps = 1000;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		List<Moon> moons = new ArrayList<>();
		for (int i = 0; i < 4; i++) {
			String line = sc.nextLine();
			int x = Integer.parseInt(line.substring(line.indexOf('=') + 1, line.indexOf(',')));
			int y = Integer
					.parseInt(line.substring(line.indexOf("y=") + 2, line.indexOf(", ", line.indexOf("y=") + 2)));
			int z = Integer.parseInt(line.substring(line.lastIndexOf("z=") + 2, line.length() - 1));

			moons.add(new Moon(new Vector(x, y, z)));
		}

		for (int i = 0; i < steps; i++) {
			for (int j = 0, len = moons.size(); j < len; j++) {
				for (int k = j + 1; k < len; k++) {
					moons.get(j).compareTo(moons.get(k));
				}
			}
			for (int j = 0, len = moons.size(); j < len; j++) {
				moons.get(j).applyGravity();
				moons.get(j).applyVelocity();
			}
		}

		int energy = 0;
		for (int j = 0, len = moons.size(); j < len; j++) {
			energy += moons.get(j).getEnergy();
		}
		System.out.println("Part one - energy: " + energy);

		long stepsX = repeatsAfter(0, moons);
		long stepsY = repeatsAfter(1, moons);
		long stepsZ = repeatsAfter(2, moons);
		System.out.println("Part two - repeats after: " + lcm(lcm(stepsX, stepsY), stepsZ));

		sc.close();
	}

	public static long repeatsAfter(int ax, List<Moon> moons) {
		long step = 0;
		HashSet<List<Integer>> allPositions = new HashSet<>();
		while (true) {
			for (int j = 0, len = moons.size(); j < len; j++) {
				for (int k = j + 1; k < len; k++) {
					moons.get(j).compareTo(moons.get(k));
				}
			}

			for (int j = 0, len = moons.size(); j < len; j++) {
				moons.get(j).applyGravity();
				moons.get(j).applyVelocity();
			}
			
			List<Integer> currentPositions = new ArrayList<>();
			for (Moon moon : moons) {
				if (ax == 0) {
					currentPositions.add(moon.getPosition().getX());
					currentPositions.add(moon.getVelocity().getX());
				} else if (ax == 1) {
					currentPositions.add(moon.getPosition().getY());
					currentPositions.add(moon.getVelocity().getY());
				} else {
					currentPositions.add(moon.getPosition().getZ());
					currentPositions.add(moon.getVelocity().getZ());
				}
			}

			if (allPositions.contains(currentPositions)) {
				return step;

			} else {
				++step;
				allPositions.add(currentPositions);
			}
		}
	}

	public static long lcm(long a, long b) {
		if (a == 0 || b == 0)
			return 0;
		return (a * b) / gcd(a, b);
	}

	private static long gcd(long a, long b) {
		long remainder = 0;
		do {
			remainder = a % b;
			a = b;
			b = remainder;
		} while (b != 0);
		return a;
	}
}
