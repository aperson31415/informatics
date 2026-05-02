async function fetchRawJson(url) {
        try {
            const response = await fetch(url);

            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }

            const rawText = await response.text();

            console.log("Raw JSON string:");
            console.log(rawText);

            try {
                const jsonData = JSON.parse(rawText);
                console.log("Parsed JSON object:");
                console.log(jsonData);
                return jsonData;
            } catch (parseError) {
                console.error("Invalid JSON format:", parseError.message);
            }

        } catch (error) {
            console.error("Error fetching JSON:", error.message);
        }
    }

    const data_name = "Testing topic";

    Vue.createApp({
        data() {
                return {
                    title: '',
                    sections: [],
                    author: '',
                    date: '',
                    loaded: false
                };
        },
        async mounted() {
            try {
                const data = await fetchRawJson("https://raw.githubusercontent.com/aperson31415/informatics/refs/heads/main/Vue%20test/data.json");
                
                if (data[data_name]) {
                    Object.assign(this.$data, data[data_name]);
                    Object.assign(this.$data.loaded, true);
                }
            } catch (err) {
                console.error("Data fetch failed:", err);
            }
        }
    }).mount('#app');