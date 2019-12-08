package hr.fer.aoc;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class Day8 {
	public static final int width = 25;
	public static final int height = 6;

	public static void main(String[] args) throws IOException {
		String line = Files.readAllLines(Paths.get("src/input.txt")).get(0);
		List<String> layers = new ArrayList<>();

		for (int i = 0; i < line.length(); i++) {
			if (i % (height * width) == 0)
				layers.add(line.substring(i, i + width * height));
		}

		String minLayer = layers.stream().min((m1, m2) -> (int) m1.chars().filter(f -> f == '0').count()
				- (int) m2.chars().filter(f -> f == '0').count()).get();
		long res = minLayer.chars().filter(f -> f == '1').count() * minLayer.chars().filter(f -> f == '2').count();
		System.out.println(res);

		for (int i = 0; i < width * height; i++) {
			if(i%width == 0) System.out.println();
			boolean flag = true;
			for (String l : layers) {
				if (l.charAt(i) != '2') {
					if (l.charAt(i) == '0') System.out.print('.');
					else System.out.print('#');
					flag = false;
					break;
				}
			}
			if(flag) System.out.print('.');
		}
	}
}
