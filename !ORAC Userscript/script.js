// ==UserScript==
// @name         ORAC Tag Manager
// @namespace    http://tampermonkey.net/
// @version      v3.0.2
// @description  Custom tags in orac, hidden problems.
// @author       a_person31415
// @match        https://orac2.info/hub/personal/*
// @match        https://orac.amt.edu.au/hub/personal/*
// @match        https://orac2.info/problem/*
// @match        https://orac.amt.edu.au/problem/*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=orac2.info
// @grant         GM_setValue
// @grant         GM_getValue
// @grant         GM_addStyle
// ==/UserScript==

(function() {
    'use strict';

    const TAG_ORDER = ["starter", "training", "aio", "acio", "aiio", "alpha", "fario", "seln", "cpp-practice", "custom-tags"];

    GM_addStyle(`
        .badge-tag { margin-right: 4px; cursor: pointer; border: 1px solid #ccc; background-color: #f8f9fa; color: #333; }
        .badge-tag.selected { background-color: #d9534f !important; color: white !important; border-color: #d43f3a !important; }
        .badge-tag:hover { opacity: 0.8; }
    `);

    function tag_element(content) {
        let elem = document.createElement("span");
        elem.classList.add("badge", "badge-tag");
        elem.innerText = content;
        return elem;
    }

    // --- PROBLEM PAGE LOGIC ---
    if(window.location.href.includes("problem")) {
        let score_badge = document.querySelector(".badge.hub-badge");
        if (score_badge) {
            // Save current score/style immediately to its own key
            GM_setValue("score_" + window.location.href, {
                score: score_badge.innerText.trim(),
                style: score_badge.className
            });
            let name = document.querySelector("h1.mb-0")?.innerText.trim();
            if (name) GM_setValue("name_" + window.location.href, name);
        }

        function render_tags_on_problem_page() {
            if (!window.bookmark_section) return;
            window.bookmark_section.innerHTML = "<br>Custom Tags: ";
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

        let info_box = document.querySelector(".mb-3");
        if (info_box) {
            window.bookmark_section = document.createElement("div");
            render_tags_on_problem_page();
            info_box.appendChild(window.bookmark_section);
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
                if(tag_content[tag_name].length == 0) delete tag_content[tag_name];
                rev_tagcontent[window.location.href] = rev_tagcontent[window.location.href].filter(tag => tag != tag_name);
                GM_setValue("tags", tag_content);
                GM_setValue("rev_tags", rev_tagcontent);
                render_tags_on_problem_page();
            }
        }
    }

    // --- HUB PAGE LOGIC ---
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

            const tags_cont = document.querySelector(".tags-container");
            tags_cont.innerHTML = `<span class="tags-description">Tags:</span>`;
            TAG_ORDER.forEach(name => {
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

                let score_elems = document.querySelectorAll("td.progress-column");
                score_elems.forEach((elem) => {
                    if (elem.innerHTML.includes("Viewed")) {
                        elem.innerHTML = `<span class="badge badge-no-submission hub-badge" size="30">0</span>`;
                    }
                });

                let starter_sets = ["starter", "starterset1", "starterset1challenge", "starterset2", "starterset2challenge", "starterset3", "starterset3challenge"];
                starter_sets.forEach((set_name) => {
                    document.querySelector(`[data-target="#problem-set-`+set_name+`"]`).parentElement.classList.add("set-tag-starter");
                    document.querySelector(`[data-target="#problem-set-`+set_name+`"]`).children[0].children[0].children[1].children[0].children[1].setAttribute("data-original-title", "Tags: starter");
                });

                let acio_sets = ["acio25"];
                acio_sets.forEach((set_name) => {
                    document.querySelector(`[data-target="#problem-set-`+set_name+`"]`).parentElement.classList.add("set-tag-acio");
                    document.querySelector(`[data-target="#problem-set-`+set_name+`"]`).children[0].children[0].children[1].children[0].children[1].setAttribute("data-original-title", "Tags: acio");
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
            if (typeof $ !== 'undefined') $('[data-toggle="tooltip"]').tooltip();
        }
        load_from_data();
    }
})();
