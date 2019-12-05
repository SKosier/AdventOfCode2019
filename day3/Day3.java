package hr.fer.aoc;

import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Day3 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String[] first = sc.nextLine().split(",");
		String[] second = sc.nextLine().split(",");
		Set<Node> set1 = getNodes(first);
		Set<Node> set2 = getNodes(second);
		set1.retainAll(set2);

		int min = Integer.MAX_VALUE;
		for (Node n : set1) {
			int dis = Math.abs(n.a) + Math.abs(n.b);
			if (dis < min && dis != 0) {
				min = dis;
			}
		}
		System.out.println(min);

		int minSteps = Integer.MAX_VALUE;
		for (Node n : set1) {
			int res = calculateSteps(n, first) + calculateSteps(n, second);
			if (res < minSteps)
				minSteps = res;
		}

		System.out.println(minSteps);
		sc.close();
	}

	private static int calculateSteps(Node node, String[] arr) {
		int steps = 0;
		Node last = new Node(0, 0);
		for (String n : arr) {
			int len = Integer.parseInt(n.substring(1));
			if (n.startsWith("D") && last.a == node.a && node.b < last.b && node.b > last.b - len) {
				steps += Math.abs(last.b - node.b + 1);
				break;
				
			} else if (n.startsWith("R") && last.b == node.b && node.a > last.a && node.a < last.a + len) {
				steps += Math.abs(last.a - node.a + 1);
				break;

			} else if (n.startsWith("U") && last.a == node.a && node.b > last.b && node.b < last.b + len) {
				steps += Math.abs(node.b - last.b + 1);
				break;

			} else if (n.startsWith("L") && last.b == node.b && node.a > last.a && node.a < last.a - len) {
				steps += Math.abs(node.a - last.a + 1);
				break;
			
			} else
				steps += len;

			if (n.startsWith("D")) {
				last.b -= len;
			}
			if (n.startsWith("R")) {
				last.a += len;
			}
			if (n.startsWith("U")) {
				last.b += len;
			}
			if (n.startsWith("L")) {
				last.a -= len;
			}
		}
		return steps;
	}

	private static Set<Node> getNodes(String[] instr) {
		Set<Node> nodes = new HashSet<>();
		Node last = new Node(0, 0);
		Node a = null;
		for (String n : instr) {
			for (int i = 0; i < Integer.parseInt(n.substring(1)); i++) {
				if (n.startsWith("D")) {
					a = new Node(last.a, last.b - 1);
				}
				if (n.startsWith("R")) {
					a = new Node(last.a + 1, last.b);
				}
				if (n.startsWith("U")) {
					a = new Node(last.a, last.b + 1);
				}
				if (n.startsWith("L")) {
					a = new Node(last.a - 1, last.b);

				}
				nodes.add(a);
				last = a;
			}
		}
		return nodes;
	}
}
