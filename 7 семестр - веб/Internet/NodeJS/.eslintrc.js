module.exports = {
 "env": {
  "browser": true,
  "commonjs": true,
  "es2021": true,
  "node": true
 },
 "extends": [
  "eslint:recommended",
  "plugin:@typescript-eslint/recommended",
  "@tinkoff/eslint-config/app"
 ],
 "parser": "@typescript-eslint/parser",
 "parserOptions": {
  "ecmaVersion": "latest",
  "sourceType": "module"
 },
 "rules": {
   'no-console': 'off',
   '@typescript-eslint/no-explicit-any': 'off',
   '@typescript-eslint/no-var-requires': 'off',
   'import/extensions': 'off'
 }
};
