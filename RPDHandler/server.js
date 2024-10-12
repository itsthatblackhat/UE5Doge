const express = require('express');
const BitcoinCore = require('bitcoin-core');
const bodyParser = require('body-parser');

const app = express();
const port = 3000;

// Dogecoin node configuration
const client = new BitcoinCore({
    host: '127.0.0.1',
    port: 18332, // Default testnet RPC port for Dogecoin
    username: 'thedogebird',
    password: 'thedogecrownbro'
});

// Middleware to parse JSON requests
app.use(bodyParser.json());

// Centralized error handling middleware
app.use((err, req, res, next) => {
    console.error('Unhandled error:', err);
    res.status(500).send({ error: 'An unexpected error occurred', details: err.message });
});

// Root route to check if the API is running
app.get('/', (req, res) => {
    console.log('Root URL accessed');
    res.send('Dogecoin API is running.');
});

// Route to create a new wallet address
app.post('/api/createwallet', async (req, res) => {
    try {
        console.log('Create wallet request received');
        const newAddress = await client.getNewAddress();
        console.log('New wallet address created:', newAddress);
        res.send({ address: newAddress });
    } catch (err) {
        console.error('Failed to create new wallet address:', err);
        res.status(500).send({ error: 'Failed to create new wallet address', details: err.message });
    }
});

// Route to get the balance for a given address (GET request)
app.get('/api/getbalance', async (req, res) => {
    const { address, minConfirmations = 0 } = req.query;
    if (!address) {
        console.log('Address is missing in request');
        res.status(400).send({ error: 'Address is required' });
        return;
    }

    try {
        console.log('Get balance request received (GET):', address);
        const balance = await client.getReceivedByAddress(address, parseInt(minConfirmations, 10));
        console.log(`Balance for ${address}:`, balance);
        res.send({ balance });
    } catch (err) {
        console.error('Failed to retrieve balance:', err);
        res.status(500).send({ error: 'Failed to retrieve balance', details: err.message });
    }
});

// Route to get the balance for a given address (POST request)
app.post('/api/getbalance', async (req, res) => {
    const { address, minConfirmations = 0 } = req.body;
    if (!address) {
        console.log('Address is missing in request');
        res.status(400).send({ error: 'Address is required' });
        return;
    }

    try {
        console.log('Get balance request received (POST):', address);
        const balance = await client.getReceivedByAddress(address, parseInt(minConfirmations, 10));
        console.log(`Balance for ${address}:`, balance);
        res.send({ balance });
    } catch (err) {
        console.error('Failed to retrieve balance:', err);
        res.status(500).send({ error: 'Failed to retrieve balance', details: err.message });
    }
});

// Route to send Dogecoin from one address to another
app.post('/api/senddogecoin', async (req, res) => {
    const { toAddress, amount } = req.body;
    if (!toAddress || typeof amount !== 'number') {
        console.log('Invalid send request:', req.body);
        res.status(400).send({ error: 'To address and a numeric amount are required' });
        return;
    }

    try {
        console.log('Send Dogecoin request received:', toAddress);
        const txId = await client.sendToAddress(toAddress, amount);
        console.log('Dogecoin sent successfully. Transaction ID:', txId);
        res.send({ txId });
    } catch (err) {
        console.error('Failed to send Dogecoin:', err);
        res.status(500).send({ error: 'Failed to send Dogecoin', details: err.message });
    }
});

// Route to list recent transactions for the wallet
app.get('/api/gettransactions', async (req, res) => {
    const { count = 10, skip = 0 } = req.query;

    try {
        console.log('Get transactions request received');
        const transactions = await client.listTransactions('*', parseInt(count, 10), parseInt(skip, 10));
        console.log('Transactions retrieved:', transactions);
        res.send({ transactions });
    } catch (err) {
        console.error('Failed to retrieve transactions:', err);
        res.status(500).send({ error: 'Failed to retrieve transactions', details: err.message });
    }
});

// Route to get the wallet info
app.get('/api/getwalletinfo', async (req, res) => {
    try {
        console.log('Get wallet info request received');
        const info = await client.getWalletInfo();
        console.log('Wallet info retrieved:', info);
        res.send({ info });
    } catch (err) {
        console.error('Failed to retrieve wallet info:', err);
        res.status(500).send({ error: 'Failed to retrieve wallet info', details: err.message });
    }
});

// Route to get a new receiving address with a label
app.post('/api/getnewaddress', async (req, res) => {
    const { label = "" } = req.body;

    try {
        console.log('Get new address request received:', label);
        const newAddress = await client.getNewAddress(label);
        console.log('New receiving address created:', newAddress);
        res.send({ address: newAddress });
    } catch (err) {
        console.error('Failed to get new address:', err);
        res.status(500).send({ error: 'Failed to get new address', details: err.message });
    }
});

// Start the server
app.listen(port, () => {
    console.log(`Dogecoin API server running at http://localhost:${port}`);
});
