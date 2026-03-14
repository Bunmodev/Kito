#pragma once
#include <filesystem>
#include <string>
#include <map>
#include <memory>
#include <iostream>

namespace fs = std::filesystem;

namespace kito::services {
    
    class ViewCrawler {
        public:
            ViewCrawler() = default;
            ~ViewCrawler() = default;

            // Method to crawl views based on some criteria
            void CrawlViews(const std::string& criteria) {
                // Implementation for crawling views based on the criteria
                std::cout << "Crawling views with criteria: " << criteria << std::endl;
            }
    };
}