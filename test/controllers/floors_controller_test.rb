# frozen_string_literal: true

require 'test_helper'

class FloorsControllerTest < ActionDispatch::IntegrationTest
  test 'should get index' do
    get floors_index_url
    assert_response :success
  end

  test 'should get new' do
    get floors_new_url
    assert_response :success
  end

  test 'should get edit' do
    get floors_edit_url
    assert_response :success
  end

  test 'should get view' do
    get floors_view_url
    assert_response :success
  end
end
