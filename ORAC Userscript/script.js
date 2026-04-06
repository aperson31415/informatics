// ==UserScript==
// @name         ORAC Userscript
// @namespace    http://tampermonkey.net/
// @version      v3.0.4
// @description  Custom tags in orac, hidden problems, difficulty approximation, searching upgrade, custom styling & ordering, editorials
// @author       a_person31415
// @match        https://orac2.info/hub/personal/*
// @match        https://orac.amt.edu.au/hub/personal/*
// @match        https://orac2.info/problem/*
// @match        https://orac.amt.edu.au/problem/*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=orac2.info
// @grant        GM_setValue
// @grant        GM_getValue
// @grant        GM_addStyle
// @grant        GM_listValues
// @grant        GM_deleteValue
// @grant        unsafeWindow
// ==/UserScript==

(function() {
    'use strict';

    function $(selector) {
        let contents = document.querySelectorAll(selector);
        if(contents.length == 1) {return contents[0];}
        return contents;
    }

    let TAG_ORDER = ["starter", "training", "aio", "acio", "aiio", "alpha", "fario", "camp", "seln", "apio", "ioi","cpp-practice", "testing", "custom-tags"];
    let NEW_TAGS = ["starter", "training", "acio", "cpp-practice", "custom-tags"];

    GM_addStyle(`
        .badge-tag { margin-right: 4px; cursor: pointer; background-color: #f8f9fa; color: #333; user-select: none;}
        .badge-tag.selected { background-color: #d9534f !important; color: white !important; border-color: #d43f3a !important; }
        .badge-tag:hover { opacity: 0.8; }
        .progress-column, .difficulty-column {bottom-border: 1px solid #dee2e6;}
        .difficulty-column {width: 30%;}
        .progress-column {width:20%;}
        .kooltable {border-spacing: 0 10px; border-collapse: separate; margin-bottom: 0rem !important;}
        .koolbutton {border: none; border-radius: .5rem; outline: none; cursor: pointer; user-select: none;}
        .koolbutton:focus {outline: none;}
        .koolbutton:hover {opacity: 0.8;}

        .slider-container { display: flex; align-items: center; width: 350px; height: 40px; }
        #rangevalue { font-size: 14px; font-weight: bold; color: #4CAF50; white-space: nowrap; min-width: 80px; }
        .slider-track { position: absolute; height: 5px; width: 100%; background: #ddd; top: 50%; transform: translateY(-50%); border-radius: 5px; z-index: 1; }
        .slider-range { position: absolute; height: 5px; background: #4CAF50; top: 50%; transform: translateY(-50%); border-radius: 5px; z-index: 2; }
        
        input[type=range] { position: absolute; width: 100%; height: 30px; top: 50%; transform: translateY(-50%); left: 0; margin: 0; pointer-events: none; -webkit-appearance: none; background: transparent; z-index: 3; }
        input[type=range]::-webkit-slider-thumb { pointer-events: all; width: 16px; height: 16px; border-radius: 50%; background: #4CAF50; cursor: pointer; -webkit-appearance: none; border: 2px solid #fff; box-shadow: 0 1px 3px rgba(0,0,0,0.3); }
        input[type=range]::-moz-range-thumb { pointer-events: all; width: 16px; height: 16px; border-radius: 50%; background: #4CAF50; cursor: pointer; border: 2px solid #fff; box-shadow: 0 1px 3px rgba(0,0,0,0.3); }
        input[type=range]:focus { outline: none; }

        .custom-search {border-radius: 0.5rem; border: 1px solid gray; margin-left: 0.25rem; height: 25px;}
        .custom-search:focus, .custom-search:hover {outline: 1px solid #343a40}

        .problemset-display[data-visible="false"] {height: 0; padding-top: 0; padding-bottom: 0; margin-top: 0; margin-bottom: 0; overflow: hidden; border: none;}
        tr[data-visible="false"] {height: 0 !important; padding-top: 0 !important; padding-bottom: 0 !important; margin-top: 0 !important; margin-bottom: 0 !important; overflow: hidden !important; border: none; visibility: hidden;}
        tr[data-visible="false"] td {padding: 0 !important; margin: 0 !important; height: 0 !important; font-size: 0 !important; line-height: 0 !important; border: none !important;}
    `);

    function styled_details(name, content, id) {
        let buttonp = document.createElement("p");
        let button = document.createElement("a");
        button.className = "btn btn-primary collapsed";
        button.setAttribute("data-toggle", "collapse");
        button.setAttribute("href", "#" + id);
        button.setAttribute("role", "button");
        button.setAttribute("aria-expanded", "false");
        button.innerText = name;
        buttonp.appendChild(button);

        let container = document.createElement("div");
        container.classList.add("collapse");
        container.id = id;
        container.setAttribute("style", "");
        let body = document.createElement("div");
        body.className = "card card-body";
        body.innerHTML = content;
        container.appendChild(body);

        let wrapper = document.createElement("span");
        wrapper.appendChild(buttonp);
        wrapper.appendChild(container);

        return wrapper;
    }

    async function problemdata(id) {
        const res = await fetch("https://raw.githubusercontent.com/aperson31415/informatics/refs/heads/main/ORAC%20Userscript/data.json");
        const doc = new DOMParser().parseFromString(await res.text(), 'text/html');
        const rawjson = doc.body.innerHTML;
        const obj = JSON.parse(rawjson);
        if(Object.keys(obj).includes(id) || Object.keys(obj).includes(id.toString())) {
            return obj[id];
        } else {
            return null;
        }
    }

    if(window.location.href.includes("problem") && window.location.href.includes("submissions")) {
        let parent = document.querySelectorAll(".container-xl")[2];
        let title = document.createElement("h2");
        title.innerText = "Hints";
        title.classList.add("mt-5");
        parent.appendChild(title);

        const url = new URL(window.location.href);
        const problem_id = parseInt(url.pathname.split("/").filter(Boolean)[1]);

        (async () => {
            let problem_data = await problemdata(problem_id);
            if(problem_data == null || problem_data == "" || problem_data == undefined || problem_data == []) {
                let wompwomp = document.createElement("p");
                wompwomp.innerText = "Sorry, no hints or solutions are available for this problem as of now. Try coming back to this problem later.";
                parent.appendChild(wompwomp);
            } else {
                // Hints
                for(let i = 0; i < problem_data.hints.length; i++) {
                    let content = "";
                    for(let j = 0; j < problem_data.hints[i].length; j++) {
                        content += problem_data.hints[i][j];
                    }
                    let curr_hint = styled_details("Hint " + (i + 1), content, "hint"+i);
                    curr_hint.appendChild(document.createElement("br"));
                    parent.appendChild(curr_hint);
                }

                // Code
                for(let i = 0; i < Object.keys(problem_data.solutions).length; i++) {
                    let codeelem = problem_data.solutions[Object.keys(problem_data.solutions)[i]];
                    let code = "";
                    for(let j = 0; j < codeelem.length; j++) {
                        code += codeelem[j] + "<br>";
                    }
                    let content = styled_details(Object.keys(problem_data.solutions)[i] + " solution", code, "sol" + Object.keys(problem_data.solutions)[i]);
                    parent.appendChild(content);
                }

                let last_update = document.createElement("p");
                last_update.innerText = "Last updated on " + problem_data.updated;
                parent.appendChild(last_update);
            }
        })();
    }

    function tag_element(content, parent = document) {
        let elem = parent.createElement("span");
        elem.classList.add("badge", "badge-tag");
        elem.innerText = content;
        return elem;
    }

    if(window.location.href.includes("problem") && !window.location.href.includes("hof") && !window.location.href.includes("submission")) {
        let score_badge = document.querySelector(".badge.hub-badge");
        if (score_badge) {
            // Save current score/style immediately to its own key
            GM_setValue("score_" + window.location.href, {
                score: score_badge.innerText.trim(),
                style: score_badge.className
            });
            let name = $("h1.mb-0")?.innerText.trim();
            if (name) GM_setValue("name_" + window.location.href, name);
        }

        function render_tags_on_problem_page() {
            if (!window.bookmark_section) return;
            window.bookmark_section.innerHTML = "Custom Tags: ";
            let curr_tags = GM_getValue("rev_tags", {});
            if (curr_tags[window.location.href]) {
                curr_tags[window.location.href].forEach(t => window.bookmark_section.appendChild(tag_element(t)));
            }
            let plus_tag = tag_element("+");
            plus_tag.onclick = () => new_tag();
            let minus_tag = tag_element("-");
            minus_tag.onclick = () => del_tag();
            window.bookmark_section.appendChild(plus_tag);
            window.bookmark_section.appendChild(minus_tag);
        }

        function rating_estimation_elem(solves) {
            let rating_benchmarks = {
                800: ["0 &#9733;", "#A52A2A"],
                500: ["1 &#9733;", "#808080"],
                300: ["2 &#9733;", "#008000"],
                200: ["3 &#9733;", "#03A89E"],
                100: ["4 &#9733;", "#0000FF"],
                50: ["5 &#9733;", "#a0a"],
                10: ["6 &#9733;", "#bb0"],
                5: ["7 &#9733;", "#ffa200"],
                2: ["8 &#9733;", "#ff7b00"],
                0: ["9 &#9733;", "#ff0000"]
            };

            let lower_bound = 0, stars = -1;

            if (solves >= 800) {lower_bound = 800; stars = 0;}
            else if(solves >= 500) {lower_bound = 500; stars = 1;}
            else if(solves >= 300) {lower_bound = 300; stars = 2;}
            else if(solves >= 200) {lower_bound = 200; stars = 3;}
            else if(solves >= 100) {lower_bound = 100; stars = 4;}
            else if(solves >= 50) {lower_bound = 50; stars = 5;}
            else if(solves >= 10) {lower_bound = 10; stars = 6;}
            else if(solves >= 5) {lower_bound = 5; stars = 7;}
            else if(solves >= 2) {lower_bound = 2; stars = 8;}
            else {lower_bound = 0; stars = 9;}

            let elem = document.createElement("b");
            elem.style.color = rating_benchmarks[lower_bound][1];
            elem.innerHTML = rating_benchmarks[lower_bound][0];

            let uncoloured = document.createElement("span");
            uncoloured.style.color = "#000000";

            if (solves != 1) {
                uncoloured.innerHTML = " (" + (solves) + " solves)";
            } else {
                uncoloured.innerHTML = " (1 solve)";
            }

            elem.appendChild(uncoloured);

            return {"elem":elem, "stars":stars};
        }

        if ($("tbody")[1]) {
            window.stats_bar = document.createElement("tr");
            window.bookmark_section = document.createElement("td");
            let diff_bar = document.createElement("td");
            diff_bar.style.textAlign = "right";
            document.querySelector(".mb-3").classList.add("kooltable");

            (async () => {
                let original_diffelem = rating_estimation_elem(await set_solvecount(window.location.href)).elem;
                original_diffelem.classList.add("text-nowrap");
                diff_bar.appendChild(original_diffelem);
            })();

            render_tags_on_problem_page();
            ($("tbody")[1]).appendChild(window.stats_bar);
            window.stats_bar.appendChild(window.bookmark_section);
            window.stats_bar.appendChild(diff_bar);
        }

        function new_tag() {
            let tag_name = prompt("Name of tag to add to problem");
            if (!tag_name) return;
            let tag_content = GM_getValue("tags", {});
            let rev_tagcontent = GM_getValue("rev_tags", {});
            if (tag_content[tag_name]) {
                tag_content[tag_name].push(window.location.href);
            } else {
                if(confirm("Create new tag '" + tag_name + "'?")) {
                    tag_content[tag_name] = [window.location.href];
                } else return;
            }
            if (!rev_tagcontent[window.location.href]) rev_tagcontent[window.location.href] = [];
            rev_tagcontent[window.location.href].push(tag_name);
            GM_setValue("tags", tag_content);
            GM_setValue("rev_tags", rev_tagcontent);
            render_tags_on_problem_page();
        }

        function del_tag() {
            let tag_name = prompt("Name of tag to delete from problem");
            if (!tag_name) return;
            let tag_content = GM_getValue("tags", {});
            let rev_tagcontent = GM_getValue("rev_tags", {});
            if (tag_content[tag_name]?.includes(window.location.href)) {
                tag_content[tag_name] = tag_content[tag_name].filter(loc => loc != window.location.href);
                if(tag_content[tag_name].length == 0) {
                    let should_deltag = confirm("Fully remove tag '" + tag_name + "'?");
                    if (should_deltag) {
                        delete tag_content[tag_name];
                    }
                }
                rev_tagcontent[window.location.href] = rev_tagcontent[window.location.href].filter(tag => tag != tag_name);
                GM_setValue("tags", tag_content);
                GM_setValue("rev_tags", rev_tagcontent);
                render_tags_on_problem_page();
            }
        }

        // Difficulty 

        async function get_solvecount(problem_url) {
            let url = problem_url + "/hof";
            try {
                const res = await fetch(url);
                const doc = new DOMParser().parseFromString(await res.text(), 'text/html');
                
                // Standard problem page
                let solversList = doc.querySelector("#solversList");
                if (solversList) {
                    return doc.querySelector("b")?.innerText || "0";
                } 
                
                // Leaderboard/Contest style problem
                let solves = 0;
                let solve_elems = doc.querySelectorAll(".solvecount");
                solve_elems.forEach((elem) => {
                    if (elem.innerText.trim() === "100") {
                        solves++;
                    }
                });
                return solves.toString();
            } catch (e) {
                return "0";
            }
        }

        async function set_solvecount(problem_url) {
            let solves = GM_getValue("solves_" + problem_url, -1);
            if (solves == -1) {
                let fetched = await get_solvecount(problem_url);
                GM_setValue("solves_" + problem_url, fetched);
                solves = fetched;
            }
            return solves;
        }


    }

    if (window.location.href.includes("personal")) {
        unsafeWindow.toggleSetTagSelected = function(elem) {
            if (elem.classList.contains("selected-tag")) {
                elem.classList.remove("selected-tag");
                localStorage.removeItem('selected-tag');
            } else {
                elem.classList.add("selected-tag");
                localStorage.setItem('selected-tag', elem.textContent.trim());
            }
            reloadHidden();
        };
    } else if(window.location.href.includes("hof")) {
        unsafeWindow.toggleLanguageFilter = function(elem, language) {
            elem.classList.toggle('selected-tag');

            // Filter submissions
            if (!elem.classList.contains('selected-tag')) {
                language = null;
            }
            const solvers = document.getElementById('solversList').getElementsByClassName('solver');
            for (let i = 0; i < solvers.length; i++) {
                solvers[i].hidden = (language && !solvers[i].classList.contains(language));
            }

            hideLastComma();
        }
    }

    if (window.location.href.includes("personal")) {
        async function get_badge_data(url) {
            // Check individual storage key first
            let entry = GM_getValue("score_" + url, null);
            
            if (!entry || typeof entry !== 'object') {
                try {
                    const res = await fetch(url);
                    const doc = new DOMParser().parseFromString(await res.text(), 'text/html');
                    let score_el = doc.querySelector(".badge.hub-badge");
                    entry = score_el ? { score: score_el.innerText.trim(), style: score_el.className } 
                                     : { score: "0", style: "badge hub-badge badge-no-submission" };
                    // Save result immediately after fetch
                    GM_setValue("score_" + url, entry);
                } catch (e) { 
                    entry = { score: "0", style: "badge hub-badge badge-no-submission" }; 
                }
            }
            return entry;
        }

        async function load_from_data() {
            let data = {
                "sets": [
                    { "tag":"training", "set_name":"Implementation Problems", "set_id":"impl", "problems": [
                        { "problem_name":"Bernard's Magic Needles", "problem_link":"https://orac2.info/problem/1106/" },
                        { "problem_name":"A Not So Simple Sort", "problem_link":"https://orac2.info/problem/1105/" },
                        { "problem_name":"Pie a la Mode", "problem_link":"https://orac2.info/problem/1111/" },
                        { "problem_name":"Stacks", "problem_link":"https://orac2.info/problem/745/" },
                        { "problem_name":"Queues", "problem_link":"https://orac2.info/problem/752/" },
                        { "problem_name":"Bracket Matching", "problem_link":"https://orac2.info/problem/1107/" },
                        { "problem_name":"Twin Primes", "problem_link":"https://orac2.info/problem/872/" },
                        { "problem_name":"Pairs", "problem_link":"https://orac2.info/problem/947/" }
                    ]},
                    { "tag":"training", "set_name":"Graph Problems", "set_id":"graph", "problems": [
                        { "problem_name":"Quicksort", "problem_link":"https://orac2.info/problem/659/" },
                        { "problem_name":"Gossip Chains", "problem_link":"https://orac2.info/problem/738/" },
                        { "problem_name":"King Arthur", "problem_link":"https://orac2.info/problem/978/" }
                    ]},
                    { "tag":"training", "set_name":"Bitmask Problems", "set_id":"bitmask", "problems": [
                        { "problem_name":"Tiling", "problem_link":"https://orac2.info/problem/935/" },
                        { "problem_name":"Odd Jobs", "problem_link":"https://orac2.info/problem/951/" },
                        { "problem_name":"King Arthur", "problem_link":"https://orac2.info/problem/978/" }
                    ]},
                    { "tag":"cpp-practice", "set_name":"C++ Starter Problems", "set_id":"cpp-starter", "problems": [
                        { "problem_name":"Addition (C++ Only)", "problem_link":"https://orac2.info/problem/1309/" },
                        { "problem_name":"Counting to Infinity (C++ Only)", "problem_link":"https://orac2.info/problem/1307/" },
                        { "problem_name":"Triple Hunting (C++ Only)", "problem_link":"https://orac2.info/problem/1306/" },
                        { "problem_name":"Sitting or Standing (C++ Only)", "problem_link":"https://orac2.info/problem/1308/" },
                        { "problem_name":"A Dish Best served Cold (C++ Only)", "problem_link":"https://orac2.info/problem/1310/" }
                    ]}
                ]
            };

            let c_tags = GM_getValue("tags", {});
            for(let t in c_tags) {
                data.sets.push({ 
                    tag: "custom-tags", set_name: "Custom Tag: " + t, set_id: "c-" + t.replace(/\s+/g, '-'), 
                    problems: c_tags[t].map(l => ({ problem_name: GM_getValue("name_" + l, "Unknown"), problem_link: l })),
                    tooltip_text: "Tags: " + t
                });
            }

            const tags_cont = $(".tags-container");

            let curr_tags = $(".badge", tags_cont);
            let ORIGINAL_TAGS = [];
            curr_tags.forEach((tag) => {
                ORIGINAL_TAGS.push(tag.innerText);
            });

            tags_cont.innerHTML = `<span class="tags-description">Tags:</span>`;
            TAG_ORDER.forEach(name => {
                if (!(NEW_TAGS.includes(name))) {
                    if (!(ORIGINAL_TAGS.includes(name))) {
                        return;
                    }
                }

                let badge = tag_element(name);
                badge.setAttribute("onclick", "toggleSetTagSelected(this);");
                tags_cont.appendChild(badge);
            });

            for (let set of data.sets) {
                let div = document.createElement("div");
                div.id = "custom_set-" + set.set_id;
                div.className = `problemset-display set-table set-tag-${set.tag}`;
                
                let tooltip = set.tooltip_text || "Tags: " + set.tag;
                div.innerHTML = `
                    <table class="table table-sm mt-0 mb-0 pointer" data-toggle="collapse" data-target="#collapse-${set.set_id}">
                        <thead class="thead-dark"><tr>
                            <th scope="col"><span class="set-title mr-auto">${set.set_name}</span></th>
                            <th scope="col" class="progress-column">
                                <div class="d-flex align-items-center">
                                    <span class="badge badge-secondary mr-auto score-display">Fetching scores...</span>
                                    <span class="fas fa-lg fa-tag" data-toggle="tooltip" data-original-title="${tooltip}"></span>
                                </div>
                            </th>
                        </tr></thead>
                    </table>
                    <div id="collapse-${set.set_id}" class="collapse show set-problems">
                        <table class="table table-sm mt-0 mb-0"><tbody id="table-${set.set_id}"></tbody></table>
                    </div>`;
                document.getElementById("show-sets").appendChild(div);

                let score_elems = $("td.progress-column");
                score_elems.forEach((elem) => {
                    if (elem.innerHTML.includes("Viewed")) {
                        elem.innerHTML = `Not attempted`;
                    }
                });

                let starter_sets = ["starter", "starterset1", "starterset1challenge", "starterset2", "starterset2challenge", "starterset3", "starterset3challenge"];
                starter_sets.forEach((set_name) => {
                    $(`[data-target="#problem-set-`+set_name+`"]`).parentElement.classList.add("set-tag-starter");
                    $(`[data-target="#problem-set-`+set_name+`"]`).children[0].children[0].children[1].children[0].children[1].setAttribute("data-original-title", "Tags: starter");
                });

                let acio_sets = ["acio25"];
                acio_sets.forEach((set_name) => {
                    $(`[data-target="#problem-set-`+set_name+`"]`).parentElement.classList.add("set-tag-acio");
                    $(`[data-target="#problem-set-`+set_name+`"]`).children[0].children[0].children[1].children[0].children[1].setAttribute("data-original-title", "Tags: acio");
                });

                let badgePromises = set.problems.map(async (p) => {
                    let tr = document.createElement("tr");
                    tr.innerHTML = `<td><a href="${p.problem_link}">${p.problem_name}</a></td><td class="progress-column"></td>`;
                    document.getElementById("table-" + set.set_id).appendChild(tr);

                    let badge_node = document.createElement("span");
                    badge_node.className = "badge badge-secondary"; 
                    badge_node.innerText = "Fetching score...";
                    tr.children[1].appendChild(badge_node);

                    let entry = await get_badge_data(p.problem_link);
                    badge_node.innerText = entry.score;
                    badge_node.className = entry.style; 
                    return entry;
                });

                Promise.all(badgePromises).then((results) => {
                    let total = results.reduce((sum, res) => sum + (parseInt(res.score) || 0), 0);
                    let attempted = results.some(res => !res.style.includes("badge-no-submission"));
                    let max = results.length * 100;

                    const score_el = div.querySelector('.score-display');
                    score_el.innerText = `${total} / ${max}`;
                    
                    let hClass = "badge-no-submission";
                    if (attempted) {
                        if (total === max) hClass = "badge-cmsgreen";
                        else if (total > 0) hClass = "badge-cmsyellow";
                        else hClass = "badge-cmsred";
                    }
                    score_el.className = 'badge mr-auto ' + hClass;
                });
            }
            if (typeof window.updateSetDisplay === 'function') window.updateSetDisplay();
            if (typeof querySelector !== 'undefined') $('[data-toggle="tooltip"]').tooltip();
        }
        load_from_data();

        // Solve counts
        function rating_estimation_elem(solves) {
            let rating_benchmarks = {
                800: ["0 &#9733;", "#A52A2A"],
                500: ["1 &#9733;", "#808080"],
                300: ["2 &#9733;", "#008000"],
                200: ["3 &#9733;", "#03A89E"],
                100: ["4 &#9733;", "#0000FF"],
                50: ["5 &#9733;", "#a0a"],
                10: ["6 &#9733;", "#bb0"],
                5: ["7 &#9733;", "#ffa200"],
                2: ["8 &#9733;", "#ff7b00"],
                0: ["9 &#9733;", "#ff0000"]
            };

            let lower_bound = 0, stars = -1;

            if (solves >= 800) {lower_bound = 800; stars = 0;}
            else if(solves >= 500) {lower_bound = 500; stars = 1;}
            else if(solves >= 300) {lower_bound = 300; stars = 2;}
            else if(solves >= 200) {lower_bound = 200; stars = 3;}
            else if(solves >= 100) {lower_bound = 100; stars = 4;}
            else if(solves >= 50) {lower_bound = 50; stars = 5;}
            else if(solves >= 10) {lower_bound = 10; stars = 6;}
            else if(solves >= 5) {lower_bound = 5; stars = 7;}
            else if(solves >= 2) {lower_bound = 2; stars = 8;}
            else {lower_bound = 0; stars = 9;}

            let elem = document.createElement("b");
            elem.style.color = rating_benchmarks[lower_bound][1];
            elem.innerHTML = rating_benchmarks[lower_bound][0];

            let uncoloured = document.createElement("span");
            uncoloured.style.color = "#000000";

            if (solves != 1) {
                uncoloured.innerHTML = " (" + (solves) + " solves)";
            } else {
                uncoloured.innerHTML = " (1 solve)";
            }

            elem.appendChild(uncoloured);

            return {"elem":elem, "stars":stars};
        }

        function star_display(stars) {
            let rating_benchmarks = {
                0: ["0 &#9733;", "#A52A2A"],
                1: ["1 &#9733;", "#808080"],
                2: ["2 &#9733;", "#008000"],
                3: ["3 &#9733;", "#03A89E"],
                4: ["4 &#9733;", "#0000FF"],
                5: ["5 &#9733;", "#a0a"],
                6: ["6 &#9733;", "#bb0"],
                7: ["7 &#9733;", "#ffa200"],
                8: ["8 &#9733;", "#ff7b00"],
                9: ["9 &#9733;", "#ff0000"]
            };
            let elem = document.createElement("b");
            elem.innerHTML = rating_benchmarks[stars][0];
            elem.style.color = rating_benchmarks[stars][1];

            return elem;
        }

        // --- SOLVE COUNT LOGIC ---
        
        async function get_solvecount(problem_url) {
            let url = problem_url + "/hof";
            try {
                const res = await fetch(url);
                const doc = new DOMParser().parseFromString(await res.text(), 'text/html');
                
                // Standard problem page
                let solversList = doc.querySelector("#solversList");
                if (solversList) {
                    return doc.querySelector("b")?.innerText || "0";
                } 
                
                // Leaderboard/Contest style problem
                let solves = 0;
                let solve_elems = doc.querySelectorAll(".solvecount");
                solve_elems.forEach((elem) => {
                    if (elem.innerText.trim() == "100") {
                        solves++;
                    }
                });
                return solves.toString();
            } catch (e) {
                return "0";
            }
        }

        async function set_solvecount(problem_url) {
            let solves = GM_getValue("solves_" + problem_url, -1);
            if (solves == -1) {
                let fetched = await get_solvecount(problem_url);
                GM_setValue("solves_" + problem_url, fetched);
                solves = fetched;
            }
            return solves;
        }

        function parent_fullysolved(problem) {
            for (let neighbour of problem.parentElement.children) {
                if (neighbour.children[1].classList.contains("difficulty-column")) {
                    if (!(neighbour.children[1].innerHTML.includes("solve"))) {
                        return false;
                    }
                } else {
                    return false;
                }
            }

            return true;
        }

        //solves

        function load_solves() {
            (async () => {
                let sets = document.querySelectorAll(".collapse.show.set-problems");

                for (const set of sets) {
                    let table = set.querySelector("table");
                    if (!table) continue;

                    let headerRow = set.parentElement.children[0].querySelector("tr");;
                    if (headerRow && !headerRow.querySelector(".th-diff")) {
                        let th = document.createElement("th");
                        th.classList.add("difficulty-column", "th-diff");
                        th.innerHTML = "";
                        // Insert after the first header (Problem Name)
                        headerRow.children[0].after(th);
                    }

                    let rows = table.querySelectorAll("tbody tr");
                    let fetchQueue = [];

                    rows.forEach(row => {
                        // Check if this row is a header row
                        if (row.querySelector("th") || row.classList.contains("thead-dark")) return;
                        // Prevent duplicate columns if script re-runs
                        if (row.querySelector(".difficulty-column")) return;

                        let diffTd = document.createElement("td");
                        diffTd.classList.add("difficulty-column");
                        diffTd.innerHTML = ""; 
                        row.children[0].after(diffTd);

                        let link = row.querySelector("a")?.href;
                        if (link) {
                            fetchQueue.push({ cell: diffTd, url: link });
                        }
                    });

                    for (const item of fetchQueue) {
                        let result = await set_solvecount(item.url);
                        item.cell.innerHTML = "";
                        item.cell.appendChild(rating_estimation_elem(result).elem);
                        let diff_col = item.cell.parentElement.parentElement.parentElement.parentElement.parentElement.querySelector("table tr .difficulty-column");
                        
                        if(diff_col.hasAttribute("min_stars")) {
                            diff_col.setAttribute("min_stars", Math.min(diff_col.getAttribute("min_stars"), rating_estimation_elem(result).stars));
                        } else {
                            diff_col.setAttribute("min_stars", rating_estimation_elem(result).stars)
                        }

                        if(diff_col.hasAttribute("max_stars")) {
                            diff_col.setAttribute("max_stars", Math.max(diff_col.getAttribute("max_stars"), rating_estimation_elem(result).stars));
                        } else {
                            diff_col.setAttribute("max_stars", rating_estimation_elem(result).stars);
                        }

                        if(parent_fullysolved(item.cell.parentElement)) {
                            if (diff_col.getAttribute("max_stars") == diff_col.getAttribute("min_stars")) {
                                diff_col.innerHTML = '';
                                diff_col.appendChild(star_display(diff_col.getAttribute("max_stars")));
                            } else {
                                diff_col.innerHTML = '';
                                let star_range_elem_to = document.createElement("span");
                                star_range_elem_to.innerText = " to ";

                                let star_range_elem = document.createElement("span");
                                star_range_elem.appendChild(star_display(diff_col.getAttribute("min_stars")));
                                star_range_elem.appendChild(star_range_elem_to)
                                star_range_elem.appendChild(star_display(diff_col.getAttribute("max_stars")));

                                diff_col.appendChild(star_range_elem);
                            }
                        }
                    }
                }
            })();
        }

        load_solves();

        let btn_solves = document.createElement("button");
        btn_solves.classList.add("koolbutton");
        btn_solves.innerHTML = "&nbsp;&nbsp;&nbsp;&nbsp;";
        let label_solves = document.createElement("label");
        label_solves.style.marginLeft = "0.45rem";
        label_solves.innerHTML = "Reload solve rates";

        btn_solves.addEventListener("click", async () => {
            const keys = await GM_listValues();
            for (const key of keys) {
                if (key.includes("solves_")) {
                    await GM_deleteValue(key);
                }
            }

            window.location.href = window.location.href;
            load_solves();
        });
        $(".custom-control.custom-switch.mb-sm-1")[1].after(label_solves);
        $(".custom-control.custom-switch.mb-sm-1")[1].after(btn_solves);

        // Difficulty selection
        let diff_choicecont = document.createElement("div");
        diff_choicecont.classList.add(".tags-container");

        let diff_choicelabel = document.createElement("span");
        diff_choicelabel.classList.add(".tags-description");
        diff_choicelabel.innerText = "Difficulty:";

        diff_choicecont.appendChild(diff_choicelabel);

        // Slider

        let slidercont = document.createElement("div"); slidercont.classList.add("slider-container");
        let slidertrack = document.createElement("div"); slidertrack.classList.add("slider-track");
        let sliderrange = document.createElement("div"); sliderrange.classList.add("slider-range"); sliderrange.id = "slider-range";
        let minslide = document.createElement("input"); minslide.id = "minRange"; minslide.setAttribute("type", "range"); minslide.setAttribute("min", "0"); minslide.setAttribute("max", "9"); minslide.setAttribute("value", "0");
        let maxslide = document.createElement("input"); maxslide.id = "maxRange"; maxslide.setAttribute("type", "range"); maxslide.setAttribute("min", "0"); maxslide.setAttribute("max", "9"); maxslide.setAttribute("value", "9");
        let sliderdisplay = document.createElement("span"); sliderdisplay.id = "rangevalue"; sliderdisplay.innerText = "0 &#9733; - 9 &#9733;";

        let sliderWrapper = document.createElement("div"); 
        sliderWrapper.style = "position:relative; width:200px; height:30px; margin-left:10px;";
        sliderWrapper.append(slidertrack, sliderrange, minslide, maxslide);
        slidercont.append(sliderdisplay, sliderWrapper);
        $(".tags-container").after(slidercont);
        updateSlider();

        function filterDiff() {
            updateSlider();
            $(".problemset-display").forEach((set) => {
                let max_allowed = parseInt(maxslide.value);
                let min_allowed = parseInt(minslide.value);
                let curr_min = parseInt(set.querySelector("table .difficulty-column").getAttribute("min_stars"));
                let curr_max = parseInt(set.querySelector("table .difficulty-column").getAttribute("max_stars"));

                if(!(curr_min >= min_allowed && curr_min <= max_allowed && curr_max >= min_allowed && curr_max <= max_allowed)) {
                    set.style.display = "none";
                } else {
                    if (!set.hidden) {
                        set.style.display = "block";
                    }
                }
            });
        }

        function updateSlider() {
            let minVal = parseInt(minslide.value);
            let maxVal = parseInt(maxslide.value);

            if (minVal > maxVal) {
                minVal = maxVal;
                minslide.value = minVal;
            }
            if (maxVal < minVal) {
                maxVal = minVal;
                maxslide.value = maxVal;
            }

            sliderdisplay.innerHTML = `<span style="color: #212529; font-weight: 400; font-size: 1rem;">Difficulty: </span>`;
            sliderdisplay.appendChild(star_display(minVal));
            sliderdisplay.innerHTML += `<span style="color: #212529; font-weight: 400; font-size: 1rem;"> - </span>`;
            sliderdisplay.appendChild(star_display(maxVal));

            // Update green range highlight
            const percentMin = (minVal / minslide.max) * 100;
            const percentMax = (maxVal / maxslide.max) * 100;
            sliderrange.style.left = percentMin + "%";
            sliderrange.style.width = (percentMax - percentMin) + "%";
        }

        minslide.addEventListener('input', filterDiff);
        maxslide.addEventListener('input', filterDiff);

        // Search bar
        let searchcont = document.createElement("div"); searchcont.classList.add("search-container");
        let searchlabel = document.createElement("span"); searchlabel.innerText = "Includes: ";
        let searchbar = document.createElement("input"); searchbar.classList.add("custom-search"); searchbar.setAttribute("placeholder", "Type a phrase");
        searchcont.appendChild(searchlabel); searchcont.appendChild(searchbar);
        $(".slider-container").after(searchcont);

        searchbar.addEventListener('input', filterSearch);

        function filterSearch() {
            let searchInput = document.querySelector(".custom-search");
            if (!searchInput) return;
            let searchphrase = searchInput.value.toLowerCase();

            document.querySelectorAll(".problemset-display.set-table").forEach((set) => {
                let oneProblemMatches = false;
                
                // 1. Check if the Category/Set Title matches the search
                let titleHeader = set.querySelector('[scope="col"]');
                let setTitle = titleHeader ? titleHeader.innerText.toLowerCase() : "";
                let setTitleMatches = setTitle.includes(searchphrase);

                let collapseDiv = set.querySelector(".collapse");
                if (!collapseDiv) return;

                let problems = collapseDiv.querySelectorAll("tr");
                problems.forEach((problem) => {
                    if (problem.querySelector("th") || problem.closest("thead")) return;

                    let problemLink = problem.querySelector("a");
                    if (!problemLink) return;

                    let problemName = problemLink.innerText.toLowerCase();
                    let problemMatches = problemName.includes(searchphrase);

                    if (searchphrase === "" || problemMatches || setTitleMatches) {
                        problem.setAttribute("data-visible", "true");
                        oneProblemMatches = true; 
                    } else {
                        problem.setAttribute("data-visible", "false");
                    }
                });

                if (searchphrase === "" || setTitleMatches || oneProblemMatches) {
                    set.setAttribute("data-visible", "true");
                } else {
                    set.setAttribute("data-visible", "false");
                }
            });
        }
    }
})();
