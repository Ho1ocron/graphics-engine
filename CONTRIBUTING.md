# Contributing

Thanks for your interest in contributing! This document explains how to get the repo, build it locally, and submit clear, reviewable changes.

---

## ✅ Before you start

- Clone the repository and initialize submodules:

```bash
git clone --recursive <repo-url> graphics-engine
cd graphics-engine
# If you already cloned:
# git submodule update --init --recursive
```

- Follow the build steps in `README.md` to build and run the project locally.

---

## 🧭 Development workflow

1. **Create a branch** from `main` for each change:
   - Feature: `feature/<short-description>`
   - Bugfix: `fix/<short-description>`
   - Docs: `docs/<short-description>`
2. Commit small logical changes with clear messages:
   - Format: `type(scope): short description` (e.g., `fix(build): correct include path`)
3. Push your branch and open a Pull Request (PR) against `main`.

---

## 🧩 Pull Request guidelines

- Keep PRs small and focused.
- Provide a clear description of the change and include steps to reproduce or test.
- Add or update tests/examples when applicable.
- Tag maintainers or request reviewers and link related issues using `#<issue-number>`.
- The project may squash or reword commits during merge.

---

## 🛠️ Build & test locally

- Use the instructions in `README.md` to configure and build the project.
- After building, run the executable from the project root:

```bash
./build/graphics-engine
```

- If you add new features, include a small example or unit tests showing expected behavior.

---

## 💻 Code style & tools

- Follow the existing code style. We prefer consistent, readable C++.
- Use `clang-format` (or your editor's formatter) on modified files before opening a PR:

```bash
clang-format -i $(git diff --name-only --diff-filter=ACM | grep -E '\.(cpp|h|c|m)$' || true)
```

- Consider adding a `.clang-format` or pre-commit hook if you plan to contribute regularly; I can add a recommended configuration on request.

---

## 🔁 Submodules

- GLFW is included as a git submodule. To update submodules locally:

```bash
git submodule update --remote --merge
```

- When changing submodule pointers, update the submodule and commit the new pointer in your branch.

---

## ❗ Reporting issues

Please include:
- OS and version
- CMake and compiler versions
- Exact steps to reproduce
- Relevant build logs or runtime output

A minimal reproducible example is extremely helpful.

---

## ✅ PR review checklist

- [ ] Builds locally
- [ ] Tests (or examples) added/updated
- [ ] Code follows style and formatting
- [ ] Documentation updated (README or inline comments)
- [ ] Submodule changes (if any) are intentional and documented

---

## 💬 Need help?

Open an issue with a description, steps to reproduce, and any error output.

---

Thanks for contributing — every improvement helps! 🎉
