# frozen_string_literal: true

require 'test_helper'

class UserDetailsControllerTest < ActionDispatch::IntegrationTest
  test 'should get index' do
    get user_details_index_url
    assert_response :success
  end

  test 'should get show' do
    get user_details_show_url
    assert_response :success
  end

  test 'should get new' do
    get user_details_new_url
    assert_response :success
  end

  test 'should get edit' do
    get user_details_edit_url
    assert_response :success
  end
end
