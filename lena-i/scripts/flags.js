const fs = require('fs');
const path = require('path');

const args = process.argv.slice(2);

if (args.length > 0) {
	const os = args[0];
	const flagsPath = path.join(__dirname, 'assets', 'flags.json');
	fs.readFile(flagsPath, (err, data) => {
		if (err) {
			console.error('[lena-i->scripts]: Error reading flags file', err);
			return;
		}
		const flags = JSON.parse(data);
		if (os in flags) {
			console.log(`${flags[os].join(' ')}`);
		} else {
			console.log(`[lena-i->scripts]: No flags defined for OS: ${os}`);
		}
	});
} else {
  	console.log('[lena-i->scripts]: Usage: node flags.js <os>');
}