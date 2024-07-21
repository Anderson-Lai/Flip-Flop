#include "Program.hpp"
#include <format>
#include <thread>
#include <iostream>
#include "Api.hpp"
#include "Time.hpp"
#include "Parse.hpp"
#include "AuctionHouse.hpp"
#include "File.hpp"

void Program::Run() {

	if (File::CreateJson()) {
		Program::Error("Program can not continue without lbin.json");
		Program::Error("Exiting program");
		return;
	}

	// on program start, retrieve all stored data from json file
	Program::ReadFileData();

	// constantly update file
	std::jthread updateFile(Program::UpdateFile);

	// constantly update price of lbins
	std::jthread updateLbins(Program::UpdateLbins);

	Program::Println("\nWaiting for a new minute");

	// main loop
	Api getFirstPage;
	while (true) {
		const long long sinceEpoch = Time::SecondsSinceEpoch();
		const long long secondsToMinute = sinceEpoch % 60;

		if (secondsToMinute != 0) {
			// forces TCP conection to stay alive
			getFirstPage.CallApi("https://api.hypixel.net/v2/skyblock/auctions?page=0");
			Program::Sleep(1000);
			continue;
		}

		Program::Println("\nThread is awake!\n");
		const auto start = Time::Now();

		const auto scrapeStart = Time::Now();
		std::vector<Item> recents = AuctionHouse::ScrapeNewBins(getFirstPage);
		const auto scrapeEnd = Time::Now();

		const auto parseStart = Time::Now();
		std::vector<Item> returned = Parse::Parse(recents);
		const auto parseEnd = Time::Now();

		// copy the highest profit-to-ratio item's auction id to clipboard
		if (!returned.empty()) {
			Program::WriteToClipboard("/viewauction " + returned.back().auctionId);
		}

		const auto& cachedPrices = AuctionHouse::GetInstance().GetCachedPrices();

		while (!returned.empty()) {

			Program::Println(std::format("Auction id: {} Item name: {}\nPrice: {} Profit: {}\n\
Cached price: {}\n", 

				// id and item name
				returned.back().auctionId, Program::ConvertToString(returned.back().itemName),
				// price and profit
				Program::AddCommas(returned.back().price), Program::AddCommas(returned.back().profit),
				// cached price
				Program::AddCommas(cachedPrices.at(returned.back().itemName))
			)); 

			returned.pop_back();
		}
		// flushes output to terminal
		std::cout.flush();

		const auto end = Time::Now();

		Program::Println("\nScraping items:");
		Time::Print(scrapeStart, scrapeEnd);

		Program::Println("\nParsing items:");
		Time::Print(parseStart, parseEnd);

		Program::Println("\nTotal time for everything:");
		Time::Print(start, end);

		Program::Println("\nThread is sleeping!");
		Program::Println("\nWaiting for a new minute");

		Program::Sleep(50'000);
	}
}


void Program::ReadFileData() {
	AuctionHouse& instance = AuctionHouse::GetInstance();

	Program::Println("\nReading from file!");
	const auto readStart = Time::Now();
	instance.SeedFromFileData();
	const auto readEnd = Time::Now();

	Time::Print(readStart, readEnd);

	Program::Println("\nScraping all bins!");

	const auto scrapeStart = Time::Now();
	instance.ScrapeAllBins();
	const auto scrapeEnd = Time::Now();

	Time::Print(scrapeStart, scrapeEnd);
}

void Program::UpdateFile() {
	while (true) {
		Program::Sleep(60'000);

		Program::Println("\nWriting to file!");

		const auto fileStart = Time::Now();
		File::WriteData();
		const auto fileEnd = Time::Now();

		Time::Print(fileStart, fileEnd);
	}
}

void Program::UpdateLbins() {
	while (true) {
		const long long sinceEpoch = Time::SecondsSinceEpoch();
		const long long secondsToMinute = sinceEpoch % 60;
		if (secondsToMinute == 5)
		{
			Program::Sleep(60'000);
			AuctionHouse& instance = AuctionHouse::GetInstance();

			Program::Println("\nScraping all bins!");

			const auto scrapeStart = Time::Now();
			instance.ScrapeAllBins();
			const auto scrapeEnd = Time::Now();

			Time::Print(scrapeStart, scrapeEnd);
		}
		else
		{
			Program::Sleep(1'000);
		}
	}
}
