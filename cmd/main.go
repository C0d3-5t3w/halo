package main

import (
	"fmt"
	"os"
	"path/filepath"
)

var LICENSE = `MIT License

Copyright (c) 2025 C0D3-5T3W 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.v
`

var CONFIG = `{
  "port": 8080,
  "address": "localhost"
}
`

var INDEX = `<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Halo Server</title>
    <link rel="stylesheet" href="/css/main.css">
</head>
<body>
    <div class="container">
        <h1>Welcome to Halo Server</h1>
        <p>A simple HTTP server written in standard C</p>
        <div class="info">
            <p><strong>Server:</strong> localhost:8080</p>
            <p><strong>Status:</strong> <span id="status">Running</span></p>
        </div>
        <div class="features">
            <h2>Features</h2>
            <ul>
                <li>Built with standard C and POSIX sockets</li>
                <li>Serves static HTML, CSS, and JavaScript</li>
                <li>Custom routing functions</li>
                <li>Configuration management</li>
            </ul>
        </div>
    </div>
    <script src="/js/main.js"></script>
</body>
</html>
`

var CSS = `* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    min-height: 100vh;
    display: flex;
    justify-content: center;
    align-items: center;
    padding: 20px;
}

.container {
    background: white;
    border-radius: 12px;
    padding: 40px;
    max-width: 600px;
    box-shadow: 0 20px 60px rgba(0, 0, 0, 0.3);
}

h1 {
    color: #667eea;
    margin-bottom: 10px;
    font-size: 2.5em;
}

h2 {
    color: #764ba2;
    margin-top: 30px;
    margin-bottom: 15px;
}

p {
    color: #555;
    line-height: 1.6;
    margin-bottom: 20px;
}

.info {
    background: #f8f9fa;
    border-left: 4px solid #667eea;
    padding: 15px;
    margin: 20px 0;
    border-radius: 4px;
}

.info p {
    margin-bottom: 8px;
}

.info p:last-child {
    margin-bottom: 0;
}

#status {
    color: #28a745;
    font-weight: bold;
}

.features ul {
    list-style: none;
    padding-left: 0;
}

.features li {
    padding: 10px 0;
    padding-left: 30px;
    position: relative;
    color: #333;
}

.features li:before {
    content: "✓";
    position: absolute;
    left: 0;
    color: #667eea;
    font-weight: bold;
    font-size: 1.2em;
}
`
var JS = `document.addEventListener('DOMContentLoaded', function() {
    const statusElement = document.getElementById('status');
    
    // Animate status
    setInterval(function() {
        statusElement.style.opacity = '0.5';
        setTimeout(function() {
            statusElement.style.opacity = '1';
        }, 500);
    }, 2000);
    
    // Add smooth transitions
    statusElement.style.transition = 'opacity 0.5s ease';
    
    console.log('Halo Server - Webpage loaded successfully');
});
`

func genDirs() {
	err := os.MkdirAll("web", 0755)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error creating web directory: %v\n", err)
		os.Exit(1)
	}

	err = os.MkdirAll("web/pages", 0755)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error creating web/pages directory: %v\n", err)
		os.Exit(1)
	}

	err = os.MkdirAll("web/assets", 0755)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error creating web/assets directory: %v\n", err)
		os.Exit(1)
	}

	err = os.MkdirAll("web/assets/css", 0755)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error creating web/assets/css directory: %v\n", err)
		os.Exit(1)
	}

	err = os.MkdirAll("web/assets/js", 0755)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error creating web/assets/js directory: %v\n", err)
		os.Exit(1)
	}
}

func genFiles() {
	if err := os.WriteFile("config.json", []byte(CONFIG), 0644); err != nil {
		fmt.Fprintf(os.Stderr, "Error creating config.json: %v\n", err)
		os.Exit(1)
	}

	if err := os.WriteFile("LICENSE", []byte(LICENSE), 0644); err != nil {
		fmt.Fprintf(os.Stderr, "Error creating LICENSE: %v\n", err)
		os.Exit(1)
	}

	webPath := filepath.Join("web/pages", "index.html")
	if err := os.WriteFile(webPath, []byte(INDEX), 0644); err != nil {
		fmt.Fprintf(os.Stderr, "Error creating index.html: %v\n", err)
		os.Exit(1)
	}

	cssPath := filepath.Join("web/assets/css", "main.css")
	if err := os.WriteFile(cssPath, []byte(CSS), 0644); err != nil {
		fmt.Fprintf(os.Stderr, "Error creating main.css: %v\n", err)
		os.Exit(1)
	}

	jsPath := filepath.Join("web/assets/js", "main.js")
	if err := os.WriteFile(jsPath, []byte(JS), 0644); err != nil {
		fmt.Fprintf(os.Stderr, "Error creating main.js: %v\n", err)
		os.Exit(1)
	}
}

func main() {
	genDirs()
	genFiles()
	fmt.Println(`Project created successfully!
    - LICENSE
    - config.json
    - web/pages/index.html
    - web/assets/css/main.css
    - web/assets/js/main.js`)
}
