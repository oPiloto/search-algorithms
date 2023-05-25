use colored::*;
use quicksort::quicksort;
use rand::Rng;
use std::{print, println, time::Instant};

fn seq_search<T: PartialEq>(vector: &[T], key: &T) -> Option<usize> {
    for (i, value) in vector.iter().enumerate() {
        if value == key {
            return Some(i);
        }
    }
    None
}

fn binary_search<T: Ord>(vector: &[T], key: &T) -> Option<usize> {
    let mut start = 0;
    let mut end = vector.len() - 1;

    while start <= end {
        let middle = (start + end) / 2;

        if &vector[middle] == key {
            return Some(middle);
        } else if &vector[middle] < key {
            start = middle + 1;
        } else {
            end = middle - 1;
        }
    }
    None
}

fn main() {
    let mut rng = rand::thread_rng();
    let list: [usize; 5] = [10_000, 100_000, 1_000_000, 10_000_000, 100_000_000];

    // Store the results to show at the end
    let mut results_seq: Vec<Vec<u128>> = vec![Vec::new(); list.len()];
    let mut results_bin: Vec<Vec<u128>> = vec![Vec::new(); list.len()];
    let mut sort_time: Vec<u128> = Vec::new();

    // Start
    for (n, num) in list.iter().enumerate() {
        let mut vector: Vec<usize> = Vec::with_capacity(*num);
        for _ in 0..*num {
            vector.push(rng.gen_range(1..=*num));
        }

        // Sequential
        println!("{}", "Sequential Search:".blue());
        for i in 0..5 {
            println!("Sequential seach number {} with {} values:", i, num);
            let key = rng.gen_range(1..=*num);

            println!("Looking for {}...", key);

            let start = Instant::now();
            if let Some(index) = seq_search(&vector, &key) {
                println!(
                    "Number: {} found at position: {}",
                    key.to_string().green(),
                    index.to_string().yellow()
                );
            } else {
                println!("{}", "Number not found.".red());
            }
            let end = start.elapsed();
            println!("Duration of execution: {} microseconds\n", end.as_micros());
            results_seq[n].push(end.as_micros());
        }

        // Time taken to sort the vector
        println!("{}", "Sorting the vector for binary search...".yellow());
        let start = Instant::now();
        quicksort(&mut vector);
        let end = start.elapsed();
        println!(
            "Duration of execution: {} microseconds or {} ms\n",
            end.as_micros(),
            end.as_millis()
        );
        sort_time.push(end.as_millis());

        // Binary
        println!("{}", "Binary Seach:".blue());
        for i in 0..5 {
            println!("Binary seach number {} with {} values:", i, num);
            let key = rng.gen_range(1..=*num);

            println!("Looking for {}...", key);

            let start = Instant::now();
            if let Some(index) = binary_search(&vector, &key) {
                println!(
                    "Number: {} found at position: {}",
                    key.to_string().green(),
                    index.to_string().yellow()
                );
            } else {
                println!("{}", "Number not found.".red());
            }
            let end = start.elapsed();
            println!("Duration of execution: {} microseconds\n", end.as_micros());
            results_bin[n].push(end.as_micros());
        }
    }

    println!(
        "{}{}",
        "\n\nEnd of execution".green(),
        "\nSequential seach time:".blue()
    );
    for (i, num) in list.iter().enumerate() {
        print!("\nList {}:", num);
        let mut add = 0;
        for ele in &results_seq[i] {
            print!(" {}micros", ele);
            add += ele;
        }
        print!(" | Average time: {}micros", add / list.len() as u128);
    }

    println!("{}", "\n\nBinary seach time:".blue());
    for (i, num) in list.iter().enumerate() {
        print!("\nList {}:", num);
        let mut add = 0;
        for ele in &results_bin[i] {
            print!(" {}micros", ele);
            add += ele;
        }
        print!(" | Time taken to sort the vector: {}ms", sort_time[i]);
        print!(" | Average time: {}micros", add / list.len() as u128);
    }
    println!("\n");
}
